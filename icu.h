 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Karim Mohamed
 *
 *******************************************************************************/
#ifndef ICU_H_
#define ICU_H_
#include"std_types.h"
/*
 ******						Definitions						******
 */
#define ICU_EDGE_SELECT_MASK 0xBF

/*
 ******						Types Declaration						******
 */

typedef enum{
	falling_edge , rising_edge
}ICU_edge_detection_type;

typedef enum{
	no_ferquency,F_clock_cpu ,F_clock_cpu_8,F_clock_cpu_64,F_clock_cpu_256
}ICU_frequency;

typedef struct{
	ICU_frequency freq;
	ICU_edge_detection_type edge;
}ICU_config_types;
/*
 ******						Function Declaration					******
 */

void ICU_init(const ICU_config_types* s_ptr);
void ICU_setCallBack(const void(*a_ptr2fun)(void));
void ICU_setEdgeSelect(const ICU_edge_detection_type edge);
void ICU_clearTimerValue(void);
void ICU_deInit(void);
uint16 ICU_get_icr_value(void);
#endif /* ICU_H_ */
