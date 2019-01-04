/*
 * BeaconManager.cpp
 *
 *  Created on: Jan 14, 2018
 *      Author: chuffman93
 */

#include "util/BeaconManager.h"
#include "core/FileManager.h"

BeaconManager::BeaconManager(ScheduleManager* sch,ACS* acs,EPS* eps,GPS* gps,RAD* rad,CDH* cdh)
: sch(sch), acs(acs), eps(eps), gps(gps), rad(rad),beaconRate(0),increasedBeaconRate(0), cdh(cdh)
{}

BeaconManager::~BeaconManager(){}

//! Manages the collection of beacon data to be sent
void BeaconManager::sendBeacon(){
	LogTags tags;
	tags += LogTag("Name", "BeaconManager");
	uint8_t baconFlag = 0x69;
	uint8_t FSWFlag = 0;
	//TODO::add GPS and CDH fields
	if(gps->beaconOut){
		Beacon b;
		b.epochTime = getCurrentTime();
		timespec t;
		clock_gettime(CLOCK_REALTIME, &t);
		b.systemTime = t.tv_sec;
		b.rebootCount = FileManager::GetReboot();
		b.satelliteMode = (uint8_t)sch->getCurrentMode();
		b.currentModeEnterTime = sch->getModeEnterTime();
		b.comPassCount = sch->getComPassCount();
		if(cdh != NULL){
			b.memory = (cdh->getCDHState()).memory;
			b.cpu1 = (cdh->getCDHState()).cpu1;
			b.cpu5 = (cdh->getCDHState()).cpu5;
			b.cpu15 = (cdh->getCDHState()).cpu15;
		}
		b.batteryStateofCharge = eps->getBatteryStateOfCharge();
		b.xyzPosition[0] = (gps->getPositionTime()).posX;
		b.xyzPosition[1] = (gps->getPositionTime()).posY;
		b.xyzPosition[2] = (gps->getPositionTime()).posZ;
		b.xyzVelocity[0]  = (gps->getPositionTime()).velX;
		b.xyzVelocity[1]  = (gps->getPositionTime()).velY;
		b.xyzVelocity[2]  = (gps->getPositionTime()).velZ;
		b.gpsWeek = (gps->getPositionTime()).GPSWeek;
		b.gpsSecond = (gps->getPositionTime()).GPSSec;
		b.radNumber = rad->RADDataNum;
		ByteStream bs;
		bs << baconFlag << FSWFlag << b.epochTime << b.systemTime <<b.rebootCount << b.satelliteMode << b.currentModeEnterTime << b.comPassCount;
		bs << b.memory << b.cpu1 << b.cpu5 << b.cpu15 << b.batteryStateofCharge;
		bs << b.xyzPosition[0] << b.xyzPosition[1] << b.xyzPosition[2];
		bs << b.xyzVelocity[0] << b.xyzVelocity[1] << b.xyzVelocity[2];
		bs << b.gpsWeek << b.gpsSecond << b.radNumber;
		std::vector<uint8_t> buff = bs.vec();
		FileManager::writeToFile(BEACON,buff);
	}


}





