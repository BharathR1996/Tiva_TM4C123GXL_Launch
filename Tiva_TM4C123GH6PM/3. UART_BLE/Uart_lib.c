/*
 * Uart_lib.c
 *
 *  Created on: 25-Jun-2021
 *      Author: bharath
 */
#include<stdint.h>
#include<stdbool.h>

#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"

int x = 0;

char initial_text[]="Welcome to BLE Demo\n";

char m_data;
char R_text[] = " --> Red LED ON\n";
char B_text[] = " --> Blue LED ON\n";
char Z_text[] = " --> all LED Off\n";


void Uart_Init(void){

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX); // PB0 IS CONFIGURED TO UART1 RX
    GPIOPinConfigure(GPIO_PB1_U1TX); // PB1 IS CONFIGURED TO UART1 TX

    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);  ///SysCtlClockGet()
    UARTStdioConfig(1, 9600, 16000000);
}

void Uart_Initial_Connect(void){
           //from Microcontroller to Smartphone using BLE

                    for(x=0; x<=19; x++)
                    {
                        UARTCharPut(UART1_BASE,initial_text[x]);
                    }
}

void Uart_data_verify(void){

    if(UARTCharsAvail(UART1_BASE))
    {
        m_data = UARTCharGet(UART1_BASE);
        UARTCharPut(UART1_BASE,m_data);     // R,B,r
        if(m_data=='r')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x02);
            for(x=0; x<=15; x++)
            {
                UARTCharPut(UART1_BASE,R_text[x]);      //r --> Red LED ON
            }
        }

        else if(m_data=='b')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x04);
            for(x=0; x<=16; x++)
            {
               UARTCharPut(UART1_BASE, B_text[x]);
            }
        }
        else if(m_data=='z')
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0x00);
            for(x=0; x<=16; x++)
            {
               UARTCharPut(UART1_BASE,Z_text[x]);
            }
        }
    }
}
