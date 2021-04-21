################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc12.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_ftm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_rtc.c \
../drivers/fsl_wdog32.c 

OBJS += \
./drivers/fsl_adc12.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_ftm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_rtc.o \
./drivers/fsl_wdog32.o 

C_DEPS += \
./drivers/fsl_adc12.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_ftm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_rtc.d \
./drivers/fsl_wdog32.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKE15Z32VLF4 -DCPU_MKE15Z32VLF4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\board" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\source" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\drivers" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\device" -I"C:\Users\Rosimar\Documents\MCUXpressoIDE_11.1.1_3241\workspace\Brasil\CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


