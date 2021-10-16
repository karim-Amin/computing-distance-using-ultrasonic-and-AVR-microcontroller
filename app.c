
#include"LCD.h"
#include"ultrasonic.h"
#include"avr/io.h"
int main(void){
	SREG |=(1<<7);// enable I-bit
	uint16 distance;
	Ultrasoinc_init();
	LCD_init();
	LCD_displayString("Distance=    cm");/*write the number start from column 10*/

	while(1){
		distance = Ultrasonic_readDistance();
		if(distance<100){
			LCD_moveCursor(0,10);
			LCD_intgerToString(distance);
			LCD_displayString(" cm ");
		}else{
			LCD_moveCursor(0,10);
			LCD_intgerToString(distance);
		}

	}
	return 0;
}

