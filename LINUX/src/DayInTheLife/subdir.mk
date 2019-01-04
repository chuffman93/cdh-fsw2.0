################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DayInTheLife/softwareTest.cpp 

OBJS += \
./src/DayInTheLife/softwareTest.o 

CPP_DEPS += \
./src/DayInTheLife/softwareTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/DayInTheLife/%.o: ../src/DayInTheLife/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DMOCK=virtual -DUBUNTU -DPRIVATE=public -I"/home/alexandrapaquin/Documents/PolarCube/cdh-fsw/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


