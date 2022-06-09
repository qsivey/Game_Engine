SimpleBGC32 Serial API Open Source C Library
==========================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam-small.png)](https://www.basecamelectronics.com)

Description
-----------
This library is a helping instrument for communication between the SimpleBGC32 devices and different data processing devices.
For more comfortable interaction with the SBGC32 devices repository contents possible examples of implementations of the
driver algorithms are presented. General source files are placed in the /sources folder. Also, you may include the
pre-made driver files if you rather to create an application using the Arduino (AVR MCUs), STM32 or Linux OS systems.

Pay attention to the **User Defined Parameter** macros contains in the core.h file. Uncomment the SYS_BIG_ENDIAN macro
if your general processing system have a BIG ENDIAN memory type. Uncomment the SBGC_DEBUG_MODE macro if you need to display
debug information. Reducing the MAX_BUFF_SIZE you also reduce the load on the stack (256 byte is a optimal value).

### Header library files involve: ###

- Macros

- Auxiliary flags and their functions

- Structure types corresponding to their commands

### Source library files involve: ###

- Data blocks for BIG ENDIAN systems

- Executable functions

The adjvar.c file contains a data block "AdjVarsDebugInfoArray" with auxiliary information about all adjustable variables
at the time of the current version. The core.c and core.h files also contain a lot of general service code.

Requirements
------------
To fully use the functions of this library, it is recommended to use a device with at least **2 KB RAM**
and at least **16 KB FLASH**.

File Descriptions
-----------------
### Source files ###

**Headers (.h):**

- adjvar/adjvar.h - Adjustable variables header file

- calib/calib.h - Calibration commands header file

- core/core.h - Header file of the core for the custom usage SBGC32 Library

- eeprom/eeprom.h - EEPROM module header file

- gimbalControl/gimbalControl.h - Gimbal realtime-control header file

- imu/imu.h - IMU module header file

- profiles/profiles.h - Profile commands header file

- realtime/realtime.h - Realtime operations header file

- service/service.h - Service functions header file

**Sources (.c):**

- adjvar/adjvar.c - Adjustable variables source file

- calib/calib.c - Calibration commands source file

- core/core.c - SBGC32 core source file

- eeprom/eeprom.c - EEPROM module source file

- gimbalControl/gimbalControl.c - Gimbal realtime-control source file

- imu/imu.c - IMU module source file

- profiles/profiles.c - Profile commands source file

- realtime/realtime.c - Realtime operations source file

- service/service.c - Service functions source file

### Driver files ###

**Headers (.h):**

- ArduinoDriver/driver_Arduino.h - STM32 driver header file

- LinuxDriver/driver_Linux.h - STM32 driver header file

- STM32_Driver/driver_STM32.h - STM32 driver header file

**Sources (.c):**

- ArduinoDriver/driver_Arduino.cpp - Arduino driver source file

- LinuxDriver/driver_Linux.c - Linux driver source file

- STM32_Driver/driver_STM32.c - STM32 driver source file

How to use this library
-----------------------
For more convenient work with the library, it is recommended to use the [SimpleBGC32 Serial API protocol
specification](https://www.basecamelectronics.com/serialapi/).

### Initialization ###

**Arduino:**

	#include "driver_Arduino.h"
	#include "core.h"
	
	GeneralSBGC_t SBGC_1;
	
	void setup ()
	{
		SBGC_SERIAL_PORT.begin(SBGC_SERIAL_SPEED);
		DEBUG_SERIAL_PORT.begin(DEBUG_SERIAL_SPEED);
		
		pinMode(SERIAL2_RX_PIN, INPUT_PULLUP);

		SBGC32_DefaultInit(&SBGC_1, UartTransmitData, UartReceiveByte, GetAvailableBytes,
						   UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);			   	
	}

**Linux:**

	#include "driver_Linux.h"
	#include "core.h"

	SBGC_1.Drv = malloc(sizeof(Driver_t));
	DriverInit(SBGC_1.Drv, SBGC_SERIAL_PORT);

	SBGC32_DefaultInit(&SBGC_1, PortTransmitData, PortReceiveByte, GetAvailableBytes,
					   PrintDebugData, GetTimeMs, SBGC_PROTOCOL_V2);


**STM32:**

*main.c :*

	#include "driver_STM32.h"
	#include "core.h"
	
	GeneralSBGC_t SBGC_1;
	
	int main (void)
	{
		USART1_Init();
		USART2_Init();
	
		SBGC_1.Drv = malloc(sizeof(Driver_t));
		DriverInit(SBGC_1.Drv, SBGC_SERIAL_PORT, INTERNAL_MAIN_TIMER);

		SBGC32_DefaultInit(&SBGC_1, UartTransmitData, UartReceiveByte, GetAvailableBytes,
						   UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);
	}
	
*stm32f7xx_it.c :*

	#include "driver_STM32.h"
	#include "core.h"
	
	extern GeneralSBGC_t SBGC_1;
	
	void TIM2_IRQHandler (void)
	{
		if (GET_FLAG_TIM_SR_UIF(INTERNAL_MAIN_TIMER) &&
		    GET_FLAG_TIM_DIER_UIE(INTERNAL_MAIN_TIMER))
			TimerDRV_CallBack(SBGC_1.Drv);

		HAL_TIM_IRQHandler(INTERNAL_MAIN_TIMER);
	}
	
	void USART1_IRQHandler (void)
	{
		if (GET_FLAG_UART_ISR_TC(SBGC_SERIAL_PORT) &&
			GET_FLAG_UART_CR1_TCIE(SBGC_SERIAL_PORT))
			UART_DRV_TxCallBack(SBGC_1.Drv);

		if (GET_FLAG_UART_ISR_RXNE(SBGC_SERIAL_PORT) &&
			GET_FLAG_UART_CR1_RXNEIE(SBGC_SERIAL_PORT))
			UART_DRV_RxCallBack(SBGC_1.Drv);

		if (GET_FLAG_UART_ISR_ORE(SBGC_SERIAL_PORT))
			CLEAR_UART_ORE(SBGC_SERIAL_PORT);

		HAL_UART_IRQHandler(SBGC_SERIAL_PORT);
	}

*Notes:*

*- Initialize the **UartTransmitDebugData** with **NULL** if you don't use debug mode;*

*- If you are connect SBGC32 through UART, RX pin must be pulled down;*

*- SBGC_x - it's a general serial connection descriptor containing data to communicate with the SBGC32 device;*

*- If you want to create your own gimbal communication driver, create it based on the necessary functions defined in the GeneralSBGC_t structure;*

*- Starting to work with the gimbal using Arduino don't forget check the **SERIAL_TX_BUFFER_SIZE** and **SERIAL_RX_BUFFER_SIZE** macros.
Strongly recommend increase this value to 256;*

*- When SBGC32 device connected with Linux device you need to set **choose mode** for this connection to **read, write and executable** 
in the terminal (sudo chmod a+rwx /dev/ttyUSBx);*

*- The communication driver for STM32 devices supports HAL and LL libraries;*

*- Default speed of SimpleBGC32 devices is a 115200 bits per second.*

### Data handling ###

Each function beginning with SBGC32_... communicates with the SBGC32 device in a different ways.

- Transmit functions required a preparing data in the target writable structures or other arguments. Such structures are
marked by **const** key word. Besides, for most -TX functions after sending data, the SBGC32 device sends a confirmation
command processed automatically in the functions body.

- Request functions require partial filling of the fields of the target structure or nothing at all. Received data is stores
in this structure. Confirmation of correct data reception is a returned status-value of this functions.

- For manual data management use the **SBGC32_TX** and **SBGC32_RX** functions.

The rest of the details are contained in the descriptions inside the library itself. Also you can generate project documentation
using doxyfile in the /doxygen folder.
