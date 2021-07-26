#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"


#define NUM_SSI_DATA            3

uint32_t pui32DataTx[NUM_SSI_DATA];
uint32_t pui32DataRx[NUM_SSI_DATA];
uint32_t ui32Index;
//volatile unsigned long g_ulSSI2RXTO = 0;


void InitConsole(void)
{
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // enable UART0 GPIO peripheral
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        UARTStdioConfig(0, 9600, SysCtlClockGet()); // 115200 baud
}


int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    InitConsole();

    UARTprintf("SSI Slave->\n");
    UARTprintf("  Mode: SPI\n");
    UARTprintf("  Data: 8-bit\n\n");

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |GPIO_PIN_2);
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);  //MISO
    GPIOPinConfigure(GPIO_PA5_SSI0TX);  //MOSI

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3,SSI_MODE_SLAVE,4000000, 8);
    SSIEnable(SSI0_BASE);

    while(SSIDataGetNonBlocking(SSI0_BASE, &pui32DataRx[0]))
    {
    }

    while(1)
    {
           while(SSIBusy(SSI0_BASE))
            {
            }
           for(ui32Index=0;ui32Index < NUM_SSI_DATA; ui32Index++)
           {
               SSIDataGet(SSI0_BASE, &pui32DataRx[ui32Index]);
                UARTprintf("%c", pui32DataRx[ui32Index]);
           }
             UARTprintf("\n");

    }
}


