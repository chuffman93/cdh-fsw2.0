################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/unittest/test_ACPInterface.cpp \
../src/test/unittest/test_ByteStream.cpp \
../src/test/unittest/test_ExternalProcess.cpp \
../src/test/unittest/test_FileManager.cpp \
../src/test/unittest/test_GPS.cpp \
../src/test/unittest/test_HotSwapInterface.cpp \
../src/test/unittest/test_Lock.cpp \
../src/test/unittest/test_Logger.cpp \
../src/test/unittest/test_MockHAL.cpp \
../src/test/unittest/test_NMEAInterface.cpp \
../src/test/unittest/test_PowerMonitorInterface.cpp \
../src/test/unittest/test_ScheduleManager.cpp \
../src/test/unittest/test_TempInterface.cpp 

OBJS += \
./src/test/unittest/test_ACPInterface.o \
./src/test/unittest/test_ByteStream.o \
./src/test/unittest/test_ExternalProcess.o \
./src/test/unittest/test_FileManager.o \
./src/test/unittest/test_GPS.o \
./src/test/unittest/test_HotSwapInterface.o \
./src/test/unittest/test_Lock.o \
./src/test/unittest/test_Logger.o \
./src/test/unittest/test_MockHAL.o \
./src/test/unittest/test_NMEAInterface.o \
./src/test/unittest/test_PowerMonitorInterface.o \
./src/test/unittest/test_ScheduleManager.o \
./src/test/unittest/test_TempInterface.o 

CPP_DEPS += \
./src/test/unittest/test_ACPInterface.d \
./src/test/unittest/test_ByteStream.d \
./src/test/unittest/test_ExternalProcess.d \
./src/test/unittest/test_FileManager.d \
./src/test/unittest/test_GPS.d \
./src/test/unittest/test_HotSwapInterface.d \
./src/test/unittest/test_Lock.d \
./src/test/unittest/test_Logger.d \
./src/test/unittest/test_MockHAL.d \
./src/test/unittest/test_NMEAInterface.d \
./src/test/unittest/test_PowerMonitorInterface.d \
./src/test/unittest/test_ScheduleManager.d \
./src/test/unittest/test_TempInterface.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/unittest/%.o: ../src/test/unittest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DMOCK=virtual -DCATCH -DPRIVATE=public -DUBUNTU -I"/home/alexandrapaquin/Documents/PolarCube/cdh-fsw/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


