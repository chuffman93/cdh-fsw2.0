/*
 * BeaconManager.h
 *
 *  Created on: Jan 10, 2018
 *      Author: chuffman93
 *
 *  - Ready for code Review
 */

#ifndef INCLUDE_UTIL_BEACONMANAGER_H_
#define INCLUDE_UTIL_BEACONMANAGER_H_

#include "test/mockhal/MockSPIManager.h"
#include "subsystem/GPS.h"
#include "subsystem/ACS.h"
#include "subsystem/EPS.h"
#include "subsystem/CDH.h"
#include "subsystem/COM.h"
#include "subsystem/RAD.h"
#include "util/TimeKeeper.h"
#include "util/ByteStream.h"
#include <vector>
#include <stdint.h>
#include <sys/sysinfo.h>


struct Beacon{
	uint32_t epochTime;
	uint32_t systemTime;
	uint32_t rebootCount;
	uint8_t satelliteMode;
	uint32_t currentModeEnterTime;
	uint32_t comPassCount;
	float timeSinceStarLock;
	float starMRP;
	std::vector<float> targetMRP;
	std::vector<float> actualMRP;
	std::vector<uint16_t> xPixel;
	std::vector<uint16_t> yPixel;
	std::vector<uint16_t> catalogID;
	uint8_t numStarsFound;
	float memory;
	float cpu1;
	float cpu5;
	float cpu15;
	uint16_t batteryStateofCharge;
	double xyzPosition[3];
	double xyzVelocity[3];
	int32_t gpsWeek;
	float gpsSecond;
	uint16_t radNumber;
};


class BeaconManager {
public:
	BeaconManager(ScheduleManager* sch,ACS* acs,EPS* eps,GPS* gps,RAD* rad,CDH* cdh); //TODO: add CDH cdh
	~BeaconManager();
	void sendBeacon();


PRIVATE:
	Beacon beacon;

	ScheduleManager* sch;
	ACS* acs;
	CDH* cdh;
	EPS* eps;
	//CDH& cdh;
	GPS* gps;
	RAD* rad;

	// TODO: Decide on how/where rates will be handled
	int32_t beaconRate;
	int32_t increasedBeaconRate;



};


#endif /* INCLUDE_UTIL_BEACONMANAGER_H_ */
