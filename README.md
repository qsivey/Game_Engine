SimpleBGC32 Serial API Open Source C Library
==========================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam-small.png)](https://www.basecamelectronics.com)

**(about library)**

Pay attention to the **User Defined Parameter** macros contains in the core.h file. Uncomment the SYS_BIG_ENDIAN macro
if your general control system has a BIG ENDIAN memory type. Uncomment the SBGC_DEBUG_MODE macro if you need to display
debug information. 

### Headers library files involve: ###

- Macros

- Auxiliary flags and them functions

- Structure types corresponding to their commands

### Sources library files involve: ###

- Data blocks for BIG ENDIAN systems

- Executable functions

The adjvar.c file also contains a data block "AdjVarsDebugInfoArray" with information about all adjustable variables
at the time of the current version. The core.c and core.h files also contain a lot of general service code.

(communication instruction)

Requirements
------------
To fully use the functions of this library, it is recommended to use a device with at least 2 KB RAM
and at least 16 KB FLASH.

File Descriptions
-----------------
### All sources files have been placed into /sources folder. ###

**Headers (.h):**

- adjvar/adjvar.h - Adjustable variables header file

- /calib/calib.h - Calibration commands header file

- /core/core.h - Header file of the core for the custom usage SBGC32 Library

- /eeprom/eeprom.h - EEPROM module header file

- /gimbalControl/gimbalControl.h - Gimbal realtime-control header file

- /imu/imu.h - IMU module header file

- /profiles/profiles.h - Profile commands header file

- /realtime/realtime.h - Realtime operations header file

- /service/service.h - Service functions header file

**Sources (.c):**

- /adjvar/adjvar.c - Adjustable variables source file

- /calib/calib.c - Calibration commands source file

- /core/core.c - SBGC32 core source file

- /eeprom/eeprom.c - EEPROM module source file

- /gimbalControl/gimbalControl.c - Gimbal realtime-control source file

- /imu/imu.c - IMU module source file

- /profiles/profiles.c - Profile commands source file

- /realtime/realtime.c - Realtime operations source file

- /service/service.c - Service functions source file

How to use this library
-----------------------
For more convenient work with the library, it is recommended to use the [SimpleBGC32 Serial API protocol
specification](https://www.basecamelectronics.com/serialapi/).
Each function beginning with SBGC32_... communicates with the SBGC32 device in a different way.

*Note: for most -TX functions after sending data the SBGC32 device sends a confirmation command processed automatically in
function body.*

### Initialization ###

**Arduino:**

	SBGC_SERIAL_PORT.begin(SBGC_SERIAL_SPEED);
	DEBUG_SERIAL_PORT.begin(DEBUG_SERIAL_SPEED);

	SBGC32_DefaultInit(&SBGC_1, UartTransmitData, UartReceiveByte, GetAvailableBytes,
 	                   UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);

**Linux:**


**STM32:**

	SBGC_1.Drv = malloc(sizeof(Driver_t));
  	DriverInit(SBGC_1.Drv, SBGC_SERIAL_PORT, INTERNAL_MAIN_TIMER);

	SBGC32_DefaultInit(&SBGC_1, UartTransmitData, UartReceiveByte, GetAvailableBytes,
 	                   UartTransmitDebugData, GetTimeMs, SBGC_PROTOCOL_V2);

*Notes:

*- initialize the **UartTransmitDebugData** with NULL if you don't use debug mode.

*- SBGC_x - it's a general serial connection descriptor containing data to communicate with the SBGC32 device

*- If you want to create your own gimbal communication driver, create it based on the type of such a structure in the library
