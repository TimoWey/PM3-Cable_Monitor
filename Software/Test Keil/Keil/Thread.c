#include <cmsis_os.h> // CMSIS RTOS header file
#include "Board_LED.h" // ::Board Support:LED

void blink_LED (void const *argument); // thread function
osThreadId tid_blink_LED; // thread id
osThreadDef (blink_LED, osPriorityNormal, 1, 0); // thread object

int Init_blink_LED (void)
{
	 tid_blink_LED = osThreadCreate (osThread(blink_LED), NULL);
	 if(!tid_blink_LED) return(-1);
	 return(0);
}
void blink_LED (void const *argument) 
{
	while (1) 
	{
		LED_On (0);
		osDelay(500);
		LED_Off (0);
		osDelay(500);
		osThreadYield();
	}
}