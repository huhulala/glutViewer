################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/viewport/glrenderviewport2D.cpp \
../src/viewport/glrenderviewport3D.cpp \
../src/viewport/glutmanager.cpp \
../src/viewport/glutviewport.cpp 

OBJS += \
./src/viewport/glrenderviewport2D.o \
./src/viewport/glrenderviewport3D.o \
./src/viewport/glutmanager.o \
./src/viewport/glutviewport.o 

CPP_DEPS += \
./src/viewport/glrenderviewport2D.d \
./src/viewport/glrenderviewport3D.d \
./src/viewport/glutmanager.d \
./src/viewport/glutviewport.d 


# Each subdirectory must supply rules for building sources it contributes
src/viewport/%.o: ../src/viewport/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


