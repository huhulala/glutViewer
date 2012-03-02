################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Interaction/camera.cpp \
../src/Interaction/glutcamera.cpp 

OBJS += \
./src/Interaction/camera.o \
./src/Interaction/glutcamera.o 

CPP_DEPS += \
./src/Interaction/camera.d \
./src/Interaction/glutcamera.d 


# Each subdirectory must supply rules for building sources it contributes
src/Interaction/%.o: ../src/Interaction/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


