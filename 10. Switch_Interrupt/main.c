#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"


int main(void)
 {
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);   //set system clock to 40MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        //Enable GPIOF peripheral since led connected to portF
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //GPIO pins 1,2,3 are set as output pins

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
    IntEnable(INT_GPIOF);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);

    while(1){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); //Turn on the LED
        SysCtlDelay(13333333);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        SysCtlDelay(13333333);
    }
    return 0;
}

void SwitchHandler(void)                         //Timer ISR
{
 GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);     //Once interrupt is generated then first clear the interrupt.
// Read the current state of the GPIO pin and+
// write back the opposite state
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02); //Turn on the LED
SysCtlDelay(13333333);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0); //Turn off the LED
}
