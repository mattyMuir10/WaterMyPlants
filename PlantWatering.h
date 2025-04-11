/*
 * PlantWatering.h
 *
 * Created: 2025-04-10 4:37:03 PM
 *  Author: mattm
 */ 


#ifndef PLANTWATERING_H_
#define PLANTWATERING_H_


#include "ADC_Hal.h"


//highest analog value (0-1023) before watering the plant - if above this value will water
#define MINIMUM_MOISTURE 100

struct WateringPlantInfo{
	volatile uint8_t* moistureSensorPowerInputOutputPort;
	uint8_t moistureSensorPowerInputOutputPin;
	volatile uint8_t* moistureSensorPowerPort;
	uint8_t moistureSensorPowerPin;
	uint8_t adcPin;
	volatile uint8_t* waterPumpInputOutputPort;
	uint8_t waterPumpInputOutputPin;
	volatile uint8_t* waterPumpPort;
	uint8_t waterPumpPin;
};

void PlantWateringInit(void);
void CheckPlants(void);
void CheckPlant(WateringPlantInfo* plantInfo, int index);
void WaterPlant(WateringPlantInfo* plantInfo);




#endif /* PLANTWATERING_H_ */