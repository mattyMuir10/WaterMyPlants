/*
 * PlantWatering.cpp
 *
 * Created: 2025-04-10 4:37:18 PM
 *  Author: mattm
 */ 
#include "PlantWatering.h"
#include "UART_HAL.h"
#include "TIMER_0.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define numberOfPlants 3

static uint8_t printBuffer[64] ={0};


//array of structs containing the info on ports and pins for respective plants
WateringPlantInfo plantsInfos [numberOfPlants] = {{&DDRB, 0, &PORTB, 0, ADC5_PIN, &DDRD, 6, &PORTD, 6},
												  {&DDRD, 4, &PORTD, 4, ADC4_PIN, &DDRD, 5, &PORTD, 5},
												  {&DDRB, 1, &PORTB, 1, ADC3_PIN, &DDRD, 7, &PORTD, 7}};
	
//set pin on given port
void SetPinOnPort(volatile uint8_t* port, uint8_t pin, uint8_t turnOn){
	
		if (turnOn != 0){
			*port |= (1 << pin);
		}
		else{
			*port &= ~(1 << pin);
		}
	
	
	
}
	
//initialize plant watering by setting adc pins and setting input output registers
void PlantWateringInit(void){
	for (int i = 0; i < numberOfPlants; i++){
		adc_pin_enable(plantsInfos[i].adcPin);
		SetPinOnPort(plantsInfos[i].waterPumpInputOutputPort, plantsInfos[i].waterPumpInputOutputPin, 1);
		SetPinOnPort(plantsInfos[i].moistureSensorPowerInputOutputPort, plantsInfos[i].moistureSensorPowerInputOutputPin, 1);
	}
}

//go through each plant and check if need water - then water if needed
void CheckPlants(void){
	for (int i = 0; i < numberOfPlants; i++){
		
		
		CheckPlant(&plantsInfos[i], i);
		
	}
	return;
}

//check if plant needs water, and water if needed
void CheckPlant(WateringPlantInfo* plantInfo, int index){
	//turn on the given moisture sensor
	SetPinOnPort(plantInfo->moistureSensorPowerPort, plantInfo->moistureSensorPowerPin, 1);
	uint32_t startMillis = millis();
	while (!millis_end(startMillis, 1));
	
	adc_source_select(plantInfo->adcPin);
	uint16_t adcConversion =adc_convert();
	
	//send a message about plant information
	memset(printBuffer, 0, sizeof(printBuffer));
	sprintf((char*)printBuffer, "Value is %u on plant number %u\n", adcConversion, index);
	uart_send_string(printBuffer);
	

	//turn off the given moisture sensor
	SetPinOnPort(plantInfo->moistureSensorPowerPort, plantInfo->moistureSensorPowerPin, 0);
		
	//if adc value is above minimum (too dry), water it
	if (adcConversion > MINIMUM_MOISTURE){
		WaterPlant(plantInfo);
	}
	return;
	
		
}

//water the given plant
void WaterPlant(WateringPlantInfo* plantInfo){
	SetPinOnPort(plantInfo->waterPumpPort, plantInfo->waterPumpPin, 1);
	//send a message about watering plant
	memset(printBuffer, 0, sizeof(printBuffer));
	sprintf((char*)printBuffer, "Watering Plant...\n");
	uart_send_string(printBuffer);
	uint32_t startMillis = millis();
	while (!millis_end(startMillis, 10000));
	SetPinOnPort(plantInfo->waterPumpPort, plantInfo->waterPumpPin, 0);
	return;
}

