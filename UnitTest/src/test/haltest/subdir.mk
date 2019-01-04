################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/haltest/test_ACPInterface.cpp \
../src/test/haltest/test_GPIOManager.cpp \
../src/test/haltest/test_GPStoACS.cpp \
../src/test/haltest/test_I2CManager.cpp \
../src/test/haltest/test_OneWireManager.cpp \
../src/test/haltest/test_RAD.cpp \
../src/test/haltest/test_RADandGPSInterface.cpp \
../src/test/haltest/test_SPIManager.cpp \
../src/test/haltest/test_UARTManager.cpp \
../src/test/haltest/test_epsPower.cpp 

OBJS += \
./src/test/haltest/test_ACPInterface.o \
./src/test/haltest/test_GPIOManager.o \
./src/test/haltest/test_GPStoACS.o \
./src/test/haltest/test_I2CManager.o \
./src/test/haltest/test_OneWireManager.o \
./src/test/haltest/test_RAD.o \
./src/test/haltest/test_RADandGPSInterface.o \
./src/test/haltest/test_SPIManager.o \
./src/test/haltest/test_UARTManager.o \
./src/test/haltest/test_epsPower.o 

CPP_DEPS += \
./src/test/haltest/test_ACPInterface.d \
./src/test/haltest/test_GPIOManager.d \
./src/test/haltest/test_GPStoACS.d \
./src/test/haltest/test_I2CManager.d \
./src/test/haltest/test_OneWireManager.d \
./src/test/haltest/test_RAD.d \
./src/test/haltest/test_RADandGPSInterface.d \
./src/test/haltest/test_SPIManager.d \
./src/test/haltest/test_UARTManager.d \
./src/test/haltest/test_epsPower.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/haltest/%.o: ../src/test/haltest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DMOCK=virtual -DCATCH -DPRIVATE=public -DUBUNTU -I"/home/alexandrapaquin/Documents/PolarCube/cdh-fsw/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


