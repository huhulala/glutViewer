################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/geometry/drawables/box.cpp \
../src/geometry/drawables/chip.cpp \
../src/geometry/drawables/coordinateAxisLines.cpp \
../src/geometry/drawables/grid.cpp 

OBJS += \
./src/geometry/drawables/box.o \
./src/geometry/drawables/chip.o \
./src/geometry/drawables/coordinateAxisLines.o \
./src/geometry/drawables/grid.o 

CPP_DEPS += \
./src/geometry/drawables/box.d \
./src/geometry/drawables/chip.d \
./src/geometry/drawables/coordinateAxisLines.d \
./src/geometry/drawables/grid.d 


# Each subdirectory must supply rules for building sources it contributes
src/geometry/drawables/%.o: ../src/geometry/drawables/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


