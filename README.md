SimpleBGC32 Serial API Open Source C Library
==========================================
[![Web-site](https://www.basecamelectronics.com/img/logo.basecam-small.png)](https://www.basecamelectronics.com)

This library is helping instrument for communication between the SimpleBGC32 devices and different data processing devices.
For more comfortable interaction with the SBGC32 devices repository contents possible examples of implementations of the
driver algorithms are presented. Include the library source files contents in the /sources folder. Also, you may use the
pre-made driver files if you rather to create an application with the Arduino (AVR MCUs), STM32 or Linux OS systems.

Pay attention to the **User Defined Parameter** macros contains in the core.h file. Uncomment the SYS_BIG_ENDIAN macro
if your general control system has a BIG ENDIAN memory type. Uncomment the SBGC_DEBUG_MODE macro if you need to display
debug information. Reducing the MAX_BUFF_SIZE you also reduce the load on the stack (256 is a optimal value).

### Header library files involve: ###

- Macros

- Auxiliary flags and them functions

- Structure types corresponding to their commands

### Source library files involve: ###

- Data blocks for BIG ENDIAN systems

- Executable functions

The adjvar.c file also contains a data block "AdjVarsDebugInfoArray" with information about all adjustable variables
at the time of the current version. The core.c and core.h files also contain a lot of general service code.

Requirements
------------
To fully use the functions of this library, it is recommended to use a device with at least **2 KB RAM**
and at least **16 KB FLASH**.

File Descriptions
-----------------
### All sources files have been placed into /sources folder. ###

**Headers (.h):**

- /adjvar/adjvar.h - Adjustable variables header file

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

*Notes:*

*- initialize the **UartTransmitDebugData** with NULL if you don't use debug mode;*

*- SBGC_x - it's a general serial connection descriptor containing data to communicate with the SBGC32 device;*

*- If you want to create your own gimbal communication driver, create it based on the type of such a structure in the library;*

*- Starting to work with the gimbal using Arduino don't forget check the **SERIAL_TX_BUFFER_SIZE** and **SERIAL_RX_BUFFER_SIZE** macros.
Strongly recommend increase this value to 256;*

*- When SBGC32 device connected with Linux device you need to set **chmod** to **-rwx** in the terminal (sudo chmod -rwx /dev/ttyUSBx);*

*- Default speed of SimpleBGC32 devices is a 115200 bits per second.*

### Data handling ###

Each function beginning with SBGC32_... communicates with the SBGC32 device in a different ways.

- Transmit functions required a preparing data in the target writable structures or other arguments. Such structures are
marked by **const** key word. Besides, for most -TX functions after sending data the SBGC32 device sends a confirmation
command processed automatically in the functions body.

- Request functions require partial filling of the fields of the target structure or nothing at all. Received data is stores
in this structure. Confirmation of correct data reception is a returned status-value of this functions.

- For manual data management use the **SBGC32_TX** and **SBGC32_RX** functions.

The rest of the details are contained in the descriptions inside the library itself.
