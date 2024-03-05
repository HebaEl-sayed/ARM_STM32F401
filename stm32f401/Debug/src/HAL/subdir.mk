################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HAL/LED.c \
../src/HAL/LED_CFG.c \
../src/HAL/SWITCH.c \
../src/HAL/SWITCH_CFG.c 

OBJS += \
./src/HAL/LED.o \
./src/HAL/LED_CFG.o \
./src/HAL/SWITCH.o \
./src/HAL/SWITCH_CFG.o 

C_DEPS += \
./src/HAL/LED.d \
./src/HAL/LED_CFG.d \
./src/HAL/SWITCH.d \
./src/HAL/SWITCH_CFG.d 


# Each subdirectory must supply rules for building sources it contributes
src/HAL/%.o: ../src/HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F410Cx -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"C:\ARM_stm32f401\workspace\stm32f401\include\APP" -I"C:\ARM_stm32f401\workspace\stm32f401\include\HAL" -I"C:\ARM_stm32f401\workspace\stm32f401\include\MCAL" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


