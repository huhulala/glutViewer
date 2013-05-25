################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/geometry/glmesh.cpp \
../src/geometry/glscene.cpp \
../src/geometry/renderable.cpp \
../src/geometry/sceneprovider.cpp 

OBJS += \
./src/geometry/glmesh.o \
./src/geometry/glscene.o \
./src/geometry/renderable.o \
./src/geometry/sceneprovider.o 

CPP_DEPS += \
./src/geometry/glmesh.d \
./src/geometry/glscene.d \
./src/geometry/renderable.d \
./src/geometry/sceneprovider.d 


# Each subdirectory must supply rules for building sources it contributes
src/geometry/%.o: ../src/geometry/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


