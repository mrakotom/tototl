################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DLPBench.cpp \
../src/OLPBench.cpp \
../src/VirtualNode.cpp \
../src/tototl.cpp 

OBJS += \
./src/DLPBench.o \
./src/OLPBench.o \
./src/VirtualNode.o \
./src/tototl.o 

CPP_DEPS += \
./src/DLPBench.d \
./src/OLPBench.d \
./src/VirtualNode.d \
./src/tototl.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -DOPENMP -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


