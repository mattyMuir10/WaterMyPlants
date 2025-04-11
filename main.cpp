/*
 * Setup.cpp
 *
 * Created: 2025-03-22 11:56:35 PM
 * Author : mattm
 */ 
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART_HAL.h"
#include "ADC_Hal.h"
#include "TIMER_0.h"
#include "PlantWatering.h"
#include "SwitchesHandler.h"





int main(void)
{
	
	
	
	
	
	timer0_init();
	SwitchesInit();
	adc_init();
	uart_init(9600, 0);
	PlantWateringInit();
	sei();
	
	
	
	
	
    WaitForEitherSwitchPress(0);
    while (1) 
    {
		
		CheckPlants();
		
		
		uint32_t startMillis = millis();
		while (!millis_end(startMillis, 30000));
		
		
		
		
		
		
    }
}

