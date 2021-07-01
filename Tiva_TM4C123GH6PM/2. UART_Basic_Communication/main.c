#include<stdint.h>
#include<stdbool.h>
#include "inc/hw_ints.h"
#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "driverlib/debug.h"

char a=0, zero=0;
int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// ENABLE GPIO PORT A,FOR UART

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);


    GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX
    GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    UARTStdioConfig(0, 9600, 16000000);                     //port num,baud rate,clock source freq

    while(1){
    UARTprintf("Hello from Tiva\n");
    SysCtlDelay(13333333);
}
}


//        while (1)
//           {
//               if (UARTCharsAvail(UART0_BASE))    //Checks if any character is present in FIFO
//               {
//                   a=UARTCharGet(UART0_BASE);
//                   UARTprintf("\n Hello from Tiva %c\n",*&a);
//
//        }
//    }
//    }

