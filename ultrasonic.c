 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: source file for ultrasonic sensor driver
 *
 * Author: Karim Mohamed
 *
 *******************************************************************************/
#include"ultrasonic.h"
#include"gpio.h"
#include"icu.h"
#include"common_macros.h"
#include"util/delay.h"
/********************************************************************************
 * 								Private Global variables
 ********************************************************************************/
static uint8 g_edge_count=0;/*to know number of edges received from the ultrasonic*/
/*to calculate the distance */
static uint16 g_echo_high_time = ULTRASONIC_ECHO_HIGH_TIME_NOT_READY;
static uint16 g_t1 ;
static uint16 g_t2;
/*
 * Description :
 * 	1)to configure the ICU driver with specific frequency and edge type
 * 	2)set call back function in ICU module will be invoked in ICU's ISR
 * 	3)set up the direction of trigger pin to be output
 */
void Ultrasoinc_init(void){
	/*Initialise the ICU driver*/
	ICU_config_types config_type = {F_clock_cpu_8,rising_edge};
	ICU_init(&config_type);
	/*set up ICU call back function*/
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	/*set up the direction for trigger pin to be output*/
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
}
/*
 * Description:
 * this function will trigger the ultrasonic sensor by send High pulse with 1us duration
 * on the trigger pin
 */
void Ultrasonic_trigger(void){
	/*to generate high pulse with duration 10 us to trigger ultrasonic */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}
/*
 * Description:
 *	this function will be called when an event triggers the ICU
 *	to measure pulse width of the echo pin
 */
void Ultrasonic_edgeProcessing(void){
	g_edge_count++;/*counts number of edges*/
	if(g_edge_count==1){
		/*change the event to falling edge*/
		ICU_setEdgeSelect(falling_edge);
		/*read the timer value at rising edge*/
		g_t1 = ICU_get_icr_value();
	}else{
		/*change the event to rising edge*/
		ICU_setEdgeSelect(rising_edge);
		/*read the timer value at falling edge*/
		g_t2 = ICU_get_icr_value();
		/*the echo high time will be the difference between T2 and T1*/
		g_echo_high_time = g_t2 - g_t1 ;
		/*to measure the time of the high pulse to start measurement again*/
		ICU_clearTimerValue();
		/*reset the edge counter*/
		g_edge_count = 0;
	}
}
/*
 * Description:
 *	this function triggers the ultrasonic sensor and the input will be Echo high time
 *	 measures and returns the distance
 */
uint16 Ultrasonic_readDistance(void){
	uint16 distance;
	/*tell the sensor to start measuring*/
	Ultrasonic_trigger();
	/*wait for ICU to capture High period and to be ready */
	while(g_echo_high_time == ULTRASONIC_ECHO_HIGH_TIME_NOT_READY);
	/*this equation from the data sheet*/
	distance = (g_echo_high_time/58.8) + 1;
	g_echo_high_time = ULTRASONIC_ECHO_HIGH_TIME_NOT_READY;
	return distance;
}
