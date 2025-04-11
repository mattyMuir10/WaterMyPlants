/*
 * ADC_Hal.cpp
 *
 * Created: 2025-03-25 2:08:02 PM
 *  Author: mattm
 */ 

#include "ADC_Hal.h"

volatile static uint8_t adc_convert_done = 1;

ISR(ADC_vect){
	adc_convert_done = 1;
}

void adc_init(void){
	ADMUX = 0b01 << REFS0;
	ADCSRA |= 1 << ADEN | 1 << ADIE | 0b111 << ADPS0;
}

void adc_pin_enable(uint8_t pin){
	DIDR0 |= 1 << pin;
}

void adc_pin_disable(uint8_t pin){
	DIDR0 &= ~(1 << pin);
}

void adc_source_select(uint8_t source){
	ADMUX &= 0xF0;
	ADMUX |= source;
}

uint16_t adc_convert(void){
	uint8_t adcl = 0;
	uint8_t adch = 0;
	
	adc_convert_done = 0;
	
	ADCSRA |= 1 << ADSC;
	while (adc_convert_done == 0);
	
	adcl = ADCL;
	adch = ADCH;
	
	return (adch << 8 | adcl);
}