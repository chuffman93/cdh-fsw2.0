/*
 * FSWthreads.cpp
 *
 *  Created on: Dec 22, 2017
 *      Author: adam
 *
 *  - Ready for Code Review
 */

#include "FSWThreads.h"
#include "subsystem/COM.h"
#include "core/ScheduleManager.h"
#include "core/GroundCommunication.h"
#include "core/Architecture.h"
#include "util/TimeKeeper.h"

using namespace std;

// Health and Status Thread
void * FSWThreads::HealthStatusThread(void * args) {
	// Use the args to set needed pointers
	HSStruct * hsStruct = (HSStruct*) args;
	Watchdog * watchdog = hsStruct->watchdog;
	EPS * eps = hsStruct->eps;
	ScheduleManager * sch = hsStruct->scheduler;
	GPS * gps = hsStruct->gps;
	// get the health and status sequence
	std::vector<SubsystemBase*> healthSeq = hsStruct->subsystemSequence;
	// Register the thread
	Logger::registerThread("H&S");
	Logger::log(LEVEL_INFO, "Starting Health and Status Thread");
	// Enter the thread
	while (1){

		watchdog->KickWatchdog();
		// Run through the sequence collecting health and status from the subsystems
		for (std::vector<SubsystemBase*>::iterator i = healthSeq.begin();
				i != healthSeq.end(); i++) {
			(*i)->getHealthStatus();
		}

		// wait 60 seconds kicking the watchdog to let it know the H&S thread isnt dead
		for(int i = 0; i <= 60; i++){
			sleep(1);
			watchdog->KickWatchdog();
		}
		// Check to see if:
		//	It is not in com mode
		//	There is no current schedule
		//	Either there is a lock or GPS is not on
		//	Make sure that it isnt needing to go into SCI, ADS, or COM modes
		if((sch->getCurrentMode() != Mode_Com) &&
				sch->scheduleEmpty() &&
				(gps->getLockStatus() || !gps->isOn()) &&
				!(FileManager::checkExistance(SCIENCE_MODE) || FileManager::checkExistance(COM_MODE) || FileManager::checkExistance(ADS_MODE))){
			// If there is no lock and gps is not on, send a default 4 hour sleep time
			if(!gps->getLockStatus() && !gps->isOn()){
				eps->sendSleepTime(14400);
			}else{
				// get the current GPSPositiontime and use it to calc sleep time
				GPSPositionTime st = gps->pt;
				uint32_t sleepTime = gps->calcSleepTime(st);
				// Make sure the sleep time makes sense before sending it to EPS
				if(sleepTime > 0){
					// Write to the COM_MODE file to make sure upon waking up it will be ready to enter com mode
					std::string writeToFile = "COM_MODE!\n";
					std::vector<std::string> buff;
					buff.push_back(writeToFile);
					FileManager::writeToStringFile(COM_MODE,buff);
					// send eps the sleep time
					eps->sendSleepTime(sleepTime);
				}
			}

		}
	}
	return NULL;
}

// Mode Thread
void * FSWThreads::ModeThread(void * args) {
	// Use the args to set needed pointers
	ModeStruct * modeStruct = (ModeStruct*) args;
	Watchdog * watchdog = modeStruct->watchdog;
	EPS* eps = modeStruct->eps;
	// get the mode sequence
	std::map<FSWMode, std::vector<SubsystemBase*> > seq = modeStruct->FSWSequence;
	ScheduleManager * scheduler = modeStruct->scheduler;
	FSWMode mode;
	// Check to make sure there isnt a new schedule in the file system
	scheduler->checkForSchedule();
	// register the mode
	Logger::registerThread("Mode");
	// if it is to go into ADS or SCI mode sleep for 10 seconds to give everything time to boot up
	if(FileManager::checkExistance(ADS_MODE) || FileManager::checkExistance(SCIENCE_MODE)){
		sleep(10);
	}
	Logger::log(LEVEL_INFO, "Starting Mode Thread");
	// enter the thread
	while (1) {
		watchdog->KickWatchdog();
		// handle the schedule if there is any changes or such
		scheduler->handleScheduling();
		// Check to see if:
		//	the Queue is not empty
		//	the Time Since Epoch is not 0 (it will be zero if it is to go into ADS or SCI on boot up
		//	The current mode is not COM
		if(!scheduler->ScheduleQueue.empty() &&
				scheduler->currentSchedule.sleepTime != 0 &&
				scheduler->CurrentMode != Mode_Com){
			// send the current schedule.sleepTime to eps as it will reflect how long we wish it to sleep for
			eps->sendSleepTime(scheduler->currentSchedule.sleepTime);
		}
		// gets the new mode if it has changed
		mode = scheduler->checkNewMode();
		Logger::Stream(LEVEL_INFO) << "Mode: " << mode;
		map<FSWMode, vector<SubsystemBase*> >::iterator it;
		it = seq.find(mode);
		// runs through the mode sequence to have the subsystems do what they need to
		if(it != seq.end()){
			for(vector<SubsystemBase*>::iterator sub = it->second.begin(); sub != it->second.end(); sub++){
				(*sub)->handleMode(mode);
			}
		}

		sleep(2);
	}
	return NULL;

}

// GPSThread
void * FSWThreads::GPSThread(void * args) {
	// Use the args to set needed pointers
	GPSStruct *gpsargs = (GPSStruct*) args;
	Watchdog * watchdog = gpsargs->watchdog;
	GPS * gps = gpsargs->gps;
	ACS* acs = gpsargs->acs;
	ScheduleManager * scheduler = gpsargs->scheduler;
	// create the File for recording GPS locations for RAD
	gps->sfFile=FileManager::createFileName(GPS_SRT_FNSH);
	std::vector<std::string> buff;
	std::string start = "";
	std::string finish = "";
	stringstream ss;
	// Register Thread
	Logger::registerThread("GPS");
	Logger::log(LEVEL_INFO, "Starting GPS Thread");
	FSWMode mode;
	// Enter the Thread
	while (1) {
		// GPS on, if lock, shut off GPS.
		for(int i = 0; i <= gps->timein; i++){
			// if gps is on, try to get a lock
			if (gps->isOn()){
				Logger::log(LEVEL_INFO,"Fetching GPS");
				gps->fetchNewGPS();
				// check if the lock was a success
				if(i < gps->timeout && !gps->getLockStatus()){
					Logger::log(LEVEL_INFO,"No Lock");
					if(gps->getLockStatus()){
						acs->sendGPS(gps->getBestXYZI());
					}
					watchdog->KickWatchdog();
					sleep(1);
					continue;
				}
				else{
					gps->powerOff();
				}
			}
			watchdog->KickWatchdog();
			// no longer sends to ACS
			acs->sendGPS(gps->getBestXYZI());
			// Collect the MODE
			mode = scheduler->getCurrentMode();
			// If it is entering Payload or in Payload and has not already got the start location
			// record it
			if((mode == Trans_BusToPayload || mode == Mode_Payload) && !(gps->stcl)){
				Logger::log(LEVEL_INFO,"Logging Start GPS Lock");
				start = "Start: ";
				ss << start << gps->getBestXYZI() << "\n";
				buff.push_back(ss.str());
				FileManager::writeToStringFile(gps->sfFile,buff);
				buff.clear();
				ss.str("");
				// set that start location has been recorded
				gps->stcl = true;
			// if it is exiting payload or out of payload and the start has been recorded
			// record the ending location
			}else if((mode == Trans_PayloadToBus || mode == Mode_Bus) && gps->stcl){
				Logger::log(LEVEL_INFO,"Logging Finish GPS Lock");
				finish = "Finish: ";
				ss << finish << gps->getBestXYZI() << "\n";
				buff.push_back(ss.str());
				FileManager::writeToStringFile(gps->sfFile,buff);
				buff.clear();
				ss.str("");
				gps->stcl = false;
			}
			sleep(1);
		}
		// reset the lock and turn it back on
		gps->resetLock();
		gps->powerOn();

	}
	return NULL;
}

// Watchdog thread
void * FSWThreads::WatchdogThread(void * args) {
	Watchdog * watchdog = (Watchdog*) args;
	Logger::registerThread("WPUP");
	Logger::log(LEVEL_INFO, "Starting Watchdog Thread");
	while (1) {
		sleep(60);
		// after a minute check on the threads
		watchdog->CheckThreads();
		Logger::Stream(LEVEL_INFO) << "Pinging from watchdog";

	}
	return NULL;
}

// Ground Thread
void * FSWThreads::GroundThread(void * args) {
	// Use the args to set needed pointers
	GroundStruct * groundStruct = (GroundStruct*) args;
	Watchdog * watchdog = groundStruct->watchdog;
	GroundCommunication * gnd = groundStruct->gnd;
	gnd->com = groundStruct->com;
	ScheduleManager * scheduler = groundStruct->scheduler;
	// Register Thread
	Logger::registerThread("GND");
	Logger::log(LEVEL_INFO, "Starting Ground Communication Thread");
	// Enter Thread
	while (1) {
		// Check to make sure the Comtimeout on GND reflects that on SCHEDULER
		if(gnd->ComTimeout != scheduler->getComTimeout()){
			gnd->ComTimeout = scheduler->getComTimeout();
		}
		// See if we are going into com mode while running through the ground comm
		bool toCom = gnd->spinGround(watchdog);
		// if toCom is true and the current mode is not COM
		// set the scheduler to COM
		if(toCom && scheduler->getCurrentMode() != Mode_Com){
			scheduler->setModeToCom();
		// if toCom is false and curret mode is COM exit COM mode
		}else if(!toCom && scheduler->getCurrentMode() == Mode_Com){
			scheduler->exitComMode();
			// run through the subsystems that use the update config function
			std::vector<SubsystemBase*> seq = Architecture::buildCFVector();
			for (std::vector<SubsystemBase*>::iterator i = seq.begin();
					i != seq.end(); i++) {
				(*i)->updateConfig();
				watchdog->KickWatchdog();
			}
			// update the schedule and filemanager configs seperatly
			scheduler->updateConfig();
			FileManager::updateConfig();
		}
		watchdog->KickWatchdog();
		sleep(1);
	}

	return NULL;
}

