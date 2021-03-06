/*
 * ScheduleManager.h
 *
 *  Created on: Dec 22, 2017
 *      Author: adam
 */

#ifndef INCLUDE_CORE_SCHEDULEMANAGER_H_
#define INCLUDE_CORE_SCHEDULEMANAGER_H_


#include <stdint.h>
#include <string>
#include <unistd.h>
#include <queue>
#include <vector>
#include <math.h>
#include "util/TimeKeeper.h"
#include "core/FileManager.h"
#include "core/FileSystem.h"
#include "util/ByteStream.h"
#include "core/Lock.h"

#define CONFIG_SCH_SIZE 8

// FSW Modes and transitions
typedef enum _FSWMode{
	Mode_Bus = 1,
	Mode_Payload = 2,
	Mode_Com = 3,
	Mode_Reset = 4,
	Trans_BusToPayload = 5,
	Trans_PayloadToBus = 6,
	Trans_BusToCom = 7,
	Trans_ComToBus = 8,
	Trans_DetumbleToBus = 9,
	Mode_Detumble = 10,
	Mode_ADS = 11,
	Trans_ADSToBus = 12,
	Trans_BusToADS = 13,
}FSWMode;

struct ScheduleStruct {
	FSWMode mode; //fsw mode
	uint32_t sleepTime; //time since boot up (seconds)
	uint32_t duration; //duration of scheduled time (seconds)
};

class ScheduleManager
{
public:
	ScheduleManager();
	~ScheduleManager();

	//check for mode changes
	FSWMode checkNewMode();
	void handleScheduling();
	//if new schedule: adds new schedule to queue, otherwise add default schedule to queue if empty
	void loadSchedule(std::string filePath);
	FSWMode handleModeChange(FSWMode current, FSWMode next);
	void setModeToCom();
	void exitComMode();
	FSWMode getCurrentMode();
	uint32_t getEpochTime();
	uint32_t getModeEnterTime();
	int getComPassCount();
	void handleConfig();
	void updateConfig();
	uint32_t getComTimeout();
	bool scheduleEmpty();
	void checkForSchedule();




PRIVATE:
	std::queue <ScheduleStruct> ScheduleQueue;
	uint32_t REBOOT_TIME; //system time of reboot
	uint32_t modeEnterTime; // system time for when current mode was entered
	int ComPassCount; // number of com passes since first start up

	ScheduleStruct currentSchedule; //SUPER confusing, this is the next scheduled item
	ScheduleStruct com; //used for when we enter com mode

	FSWMode CurrentMode; // current FSW mode

	bool acsDetumble; // Don't need this anymore since we are no longer concerned with detumbles

	Lock lock;

	//updates default schedule file
	void updateDefaultSchedule();

	LogTags tags;

};

#endif /* INCLUDE_CORE_SCHEDULEMANAGER_H_ */
