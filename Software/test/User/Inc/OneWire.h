
#ifndef STM32_DS18X20_ONEWIRE_H
#define STM32_DS18X20_ONEWIRE_H

#include <stdint.h>

#define ONEWIRE_NOBODY 				0xF0 //cmd for search ROM
#define ONEWIRE_SEARCH 				0xF0 //cmd for search ROM
#define ONEWIRE_SKIP_ROM 			0xCC  //cmd for skipped ROM
#define ONEWIRE_READ_ROM 			0x33
#define ONEWIRE_MATCH_ROM 			0x55 //cmd read target device ROM
#define ONEWIRE_CONVERT_TEMPERATURE 0x44
#define ONEWIRE_READ_SCRATCHPAD 	0xBE    //cmd read ROM memory
#define ONEWIRE_WRITE_SCRATCHPAD 	0x4E   //cmd write ROM memory
#define ONEWIRE_COPY_SCRATCHPAD 	0x48
#define ONEWIRE_RECALL_E2 			0xB8

#ifndef MAXDEVICES_ON_THE_BUS
	#define MAXDEVICES_ON_THE_BUS 		0x02  // maximum planned number of devices on the bus
#endif

#define DS18B20 	0x28  //code for device family
#define DS18S20 	0x10  //code for device family

#define WIRE_0    	0x00
#define WIRE_1    	0xff
#define OW_READ   	0xff

#define DS18B20_MEASURE_DELAY 5000

#define DS18B20_TRANSFORM_TEMP_ID	0x00
#define DS18B20_TRASISTOR_TEMP_ID	0x01

typedef struct {
  int8_t inCelsus;
  uint8_t frac;
} Temperature;

typedef struct
{
  uint8_t family;
  uint8_t code[6];
  uint8_t crc;
} RomCode;

typedef struct
{
  uint8_t crc;
  uint8_t reserved[3];
  uint8_t configuration;
  uint8_t tl;
  uint8_t th;
  uint8_t temp_msb;
  uint8_t temp_lsb;
} Scratchpad_DS18B20;

typedef struct
{
  uint8_t crc;
  uint8_t count_per;
  uint8_t count_remain;
  uint8_t reserved[2];
  uint8_t tl;
  uint8_t th;
  uint8_t temp_msb;
  uint8_t temp_lsb;
} Scratchpad_DS18S20;

typedef struct
{
  RomCode ids[MAXDEVICES_ON_THE_BUS]; //id's for all devices on bus
  int32_t lastDiscrepancy;
  uint8_t lastROM[8];
} OneWire;

typedef struct
{
	uint8_t device;
	char info[30];
}DEVInfo;

typedef struct
{
	uint32_t time_start;
	uint32_t time_diff;
	int16_t temperature;
	uint8_t id;
}DS18B20_DATA;


void usart_setup_(uint32_t baud);

uint16_t owResetCmd(void);

uint8_t owSearchCmd(OneWire *ow);

void owSkipRomCmd(OneWire *ow);

uint8_t owCRC8(RomCode *rom);

void owMatchRomCmd(RomCode *rom);

void owConvertTemperatureCmd(OneWire *ow, RomCode *rom);

uint8_t* owReadScratchpadCmd(OneWire *ow, RomCode *rom, uint8_t *data);

void owCopyScratchpadCmd(OneWire *ow, RomCode *rom);

void owRecallE2Cmd(OneWire *ow, RomCode *rom);

Temperature readTemperature(OneWire *ow, RomCode *rom, uint8_t reSense);

void owSend(uint16_t data);

void owSendByte(uint8_t data);

uint16_t owEchoRead(void);

void owReadHandler(void);



int8_t DS18B20_GetId (void);
void DS18B20_GetTemperature(DS18B20_DATA *data);
void DS18B20_Process(DS18B20_DATA *data);

#endif //STM32_DS18X20_ONEWIRE_H
