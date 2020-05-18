/*
 * DC_motor.c
 *
 * Created: 17/05/2020 8:56:26 PM
 *  Author: M
 */ 
#include "PWM.h"
#include "ADC.h"
#include "LCD.h"
uint8_t flag=0;
uint8_t grd=0;
uint16_t adc_value=0;
int main(void)
{
	SETBIT(MCUCR,ISC00);
	SETBIT(MCUCR,ISC01);
	SETBIT(GICR,INT0);
	sei();
	LCD_init();
	ADC_init();
	PWM_init_timer1_oc1a();
	PWM_init_timer1_oc1b();
	set_duty_oc1a(adc_value);
	set_duty_oc1b(adc_value);
	while(1)
    {
		adc_value = ADC_read();
    	adc_value=adc_value *100.0/1023.0;
		LCD_write_command(0x01);
		LCD_write_num(adc_value);
		LCD_write_command(0x83);
		LCD_write_char('%');
		if (OCR1B==0){set_duty_oc1a(adc_value);}
		else {set_duty_oc1b(adc_value);}
		_delay_ms(100);
		
			 }
}
ISR(INT0_vect){
	
	if (flag==0){
	set_duty_oc1b(adc_value);
	set_duty_oc1a(grd);
	flag=1;
		}	
	else if (flag==1){
		set_duty_oc1b(grd);
		set_duty_oc1a(adc_value);
		flag=0;
			
	}
	}