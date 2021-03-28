################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/game.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/spi.c \
../Core/Src/ssd1306.c \
../Core/Src/ssd1306_fonts.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/game.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/spi.o \
./Core/Src/ssd1306.o \
./Core/Src/ssd1306_fonts.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/game.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/spi.d \
./Core/Src/ssd1306.d \
./Core/Src/ssd1306_fonts.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/adc.o: ../Core/Src/adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/game.o: ../Core/Src/game.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/game.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gpio.o: ../Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/spi.o: ../Core/Src/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/ssd1306.o: ../Core/Src/ssd1306.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/ssd1306.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/ssd1306_fonts.o: ../Core/Src/ssd1306_fonts.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/ssd1306_fonts.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_hal_msp.o: ../Core/Src/stm32f7xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_it.o: ../Core/Src/stm32f7xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f7xx.o: ../Core/Src/system_stm32f7xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Core/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/user/STM32Cube/Repository/STM32Cube_FW_F7_V1.16.1/Drivers/CMSIS/Include -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f7xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

