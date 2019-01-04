#ifdef CDHBUILD
#define ROOT_DIRECTORY	 		"/"
#endif

#ifdef UBUNTU
#define ROOT_DIRECTORY			"./"
#endif

#define HOME_DIRECTORY			ROOT_DIRECTORY 		"home/root"
#define UPLINK_DIRECTORY		ROOT_DIRECTORY		"opt/uplink"
#define DOWNLINK_DIRECTORY		ROOT_DIRECTORY		"opt/downlink/"
#define BEACON_DIRECTORY		ROOT_DIRECTORY		"opt/beacon"
#define HEALTH_DIRECTORY		ROOT_DIRECTORY		"SD_2/HST"
#define COMMAND_DIRECTORY		ROOT_DIRECTORY		"SD_2/CMD/CMD"
#define LOG_MESSAGES			ROOT_DIRECTORY  	"SD_3/LOG/LOG"
#define RAD_FILE_PATH			ROOT_DIRECTORY		"SD_3/RAD/RAD" // Science data
#define GPS_SRT_FNSH			ROOT_DIRECTORY		"SD_3/RAD/GPS"

#define COM_PASS_COUNT			HOME_DIRECTORY		"/CPC.txt"
#define REBOOT_FILE				HOME_DIRECTORY		"/RBT.txt"
#define CONFIG_DIRECTORY		HOME_DIRECTORY		"/config"
#define RAD_TMP_DATA			HOME_DIRECTORY		"/RAD_TMP_DATA"
#define TX_FILE					HOME_DIRECTORY		"/TXF"
#define SCIENCE_MODE			HOME_DIRECTORY		"/SCI"
#define COM_MODE				HOME_DIRECTORY		"/COM"
#define ADS_MODE				HOME_DIRECTORY		"/ADS"

#define NEW_SCH					UPLINK_DIRECTORY	"/SCH.bin"
#define SOT_PATH				UPLINK_DIRECTORY	"/SOT.txt"
#define IEF_PATH				UPLINK_DIRECTORY	"/IEF.txt"
#define PPE_PATH				UPLINK_DIRECTORY	"/PPE.txt"
#define ACS_CONFIG_UP			UPLINK_DIRECTORY	"/ConfigUpACS"
#define GPS_CONFIG_UP			UPLINK_DIRECTORY	"/ConfigUpGPS"
#define RAD_MOTOR_CONFIG_UP		UPLINK_DIRECTORY	"/ConfigUpRADMotor"
#define RAD_DATA_CONFIG_UP		UPLINK_DIRECTORY	"/ConfigUpRADData"
#define GND_CONFIG_UP			UPLINK_DIRECTORY	"/ConfigUpGND"
#define SCH_CONFIG_UP			UPLINK_DIRECTORY	"/ConfigUpSCH"
#define FMG_CONFIG_UP 			UPLINK_DIRECTORY	"/ConfigUpFMG"

#define DFL_PATH				HOME_DIRECTORY		"/DFL.txt"

#define BEACON					BEACON_DIRECTORY	"/beacon"

#define ACS_CONFIG				CONFIG_DIRECTORY	"/ConfigACS"
#define GPS_CONFIG				CONFIG_DIRECTORY	"/ConfigGPS"
#define RAD_MOTOR_CONFIG		CONFIG_DIRECTORY	"/ConfigRADMotor"
#define RAD_DATA_CONFIG			CONFIG_DIRECTORY	"/ConfigRADData"
#define GND_CONFIG				CONFIG_DIRECTORY	"/ConfigGND"
#define SCH_CONFIG				CONFIG_DIRECTORY	"/ConfigSCH"
#define FMG_CONFIG 				CONFIG_DIRECTORY	"/ConfigFMG"

#define ACS_PATH			"/ACS"
#define CDH_PATH			"/CDH"
#define COM_PATH			"/COM"
#define EPS_PATH			"/EPS"
#define GPS_PATH			"/GPS"
#define RAD_PATH			"/RAD"
