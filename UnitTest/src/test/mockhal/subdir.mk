################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/mockhal/MockGPIOManager.cpp \
../src/test/mockhal/MockSPIManager.cpp 

OBJS += \
./src/test/mockhal/MockGPIOManager.o \
./src/test/mockhal/MockSPIManager.o 

CPP_DEPS += \
./src/test/mockhal/MockGPIOManager.d \
./src/test/mockhal/MockSPIManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/mockhal/%.o: ../src/test/mockhal/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DMOCK=virtual -DCATCH -DPRIVATE=public -DUBUNTU -I"/home/alexandrapaquin/Documents/PolarCube/cdh-fsw/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


