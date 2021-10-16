/******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: header file for ultrasonic sensor driver
 *
 * Author: Karim Mohamed
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ULTRASONIC_TRIGGER_PORT_ID PORTD_ID
#define ULTRASONIC_TRIGGER_PIN_ID  PIN5_ID
#define ULTRASONIC_ECHO_HIGH_TIME_NOT_READY -1
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Ultrasoinc_init(void);
void Ultrasonic_trigger(void);
void Ultrasonic_edgeProcessing(void);
uint16 Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */
