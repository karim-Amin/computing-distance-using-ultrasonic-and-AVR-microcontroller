 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: source file for the AVR ICU driver
 *
 * Author: Karim Mohamed
 *
 *******************************************************************************/

#include"icu.h"
#include"common_macros.h"
#include<avr/interrupt.h>
#include<avr/io.h>
/************************************private global var.********************************************/
static volatile void (*g_function_ptr)(void) = NULL_PTR;
/**********************************************************************************************************
 *											ISR															*
 ***********************************************************************************************************/
ISR(TIMER1_CAPT_vect){
	if(g_function_ptr != NULL_PTR){
		(*g_function_ptr)();
	}
}
/*
 * ***					Functions Definitions              *****
 */
/*
 * Description: to initialise the AVR ICU module
 * 1) choose the normal mode for the Timer1
 * 2) insert the values of the edge select and Frequency
 * 3) enable the interrupt module
 */
void ICU_init(const ICU_config_types* s_ptr){
	/*set the direction of ICP1/PD6 pin is input */
	DDRD &=~(1<<PD6);/*this is the only pin for the ICU module in AVR*/
	/* let Timer1 works with normal overflow mode*/
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	/*choose the event which will trigger the input capture unit*/
	TCCR1B = (TCCR1B & ICU_EDGE_SELECT_MASK) | ((s_ptr->edge)<< ICES1);
	/*choose the clock select option based on the configuration structure */
	TCCR1B = (TCCR1B & 0xE0) | ((s_ptr->freq) & 0x07);
	TCNT1 = 0;/* clear the timer /counter register*/
	ICR1 = 0;/* clear the input capture register*/
	SET_BIT(TIMSK,TICIE1);/* enable the module interrupt*/
}
/*
 * Description: modify the Edge or the event will trigger the interrupt
 */
void ICU_setEdgeSelect(const ICU_edge_detection_type edge){
	/*choose the event which will trigger the input capture unit*/
	TCCR1B = (TCCR1B & ICU_EDGE_SELECT_MASK) | ((edge)<< ICES1);
}
void ICU_setCallBack(const void(*a_ptr2fun)(void)){
	/*copy the address of the passed function in global pointer*/
	g_function_ptr =(volatile void(*)(void)) a_ptr2fun;
}

void ICU_clearTimerValue(void){
	TCNT1 = 0;
}
void ICU_deInit(void){
	/*clear all Timer registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	//disable the module interrupt
	CLEAR_BIT(TIMSK,TICIE1);
}
uint16 ICU_get_icr_value(){
	return ICR1;
}
