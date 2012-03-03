################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/base/math/mat4.cpp \
../src/base/math/quaternion.cpp 

OBJS += \
./src/base/math/mat4.o \
./src/base/math/quaternion.o 

CPP_DEPS += \
./src/base/math/mat4.d \
./src/base/math/quaternion.d 


# Each subdirectory must supply rules for building sources it contributes
src/base/math/%.o: ../src/base/math/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


