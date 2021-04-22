################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Brasil.c \
../source/display.c \
../source/interrupcoes.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/Brasil.o \
./source/display.o \
./source/interrupcoes.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/Brasil.d \
./source/display.d \
./source/interrupcoes.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKE15Z32VLF4 -DCPU_MKE15Z32VLF4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\board" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\source" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\drivers" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\device" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


