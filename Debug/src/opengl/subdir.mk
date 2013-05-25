################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opengl/pbuffer.cpp 

OBJS += \
./src/opengl/pbuffer.o 

CPP_DEPS += \
./src/opengl/pbuffer.d 


# Each subdirectory must supply rules for building sources it contributes
src/opengl/%.o: ../src/opengl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


