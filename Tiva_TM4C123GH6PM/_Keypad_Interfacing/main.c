#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"


//GLOBAL DECLARATIONS
//ROW PINS Port D
#define R1 GPIO_PIN_0
#define R2 GPIO_PIN_1
#define R3 GPIO_PIN_2
#define R4 GPIO_PIN_3

//COLUMN PINS Port C
#define C1 GPIO_PIN_4
#define C2 GPIO_PIN_5
#define C3 GPIO_PIN_6
#define C4 GPIO_PIN_7


//FUNCTION DECLARATIONS


void tiva_init();
void Cout_Rin_init();       // Column will have zeros and rows will have ones
void Cin_Rout_init();       // Columns will have ones and rows will have zeros
void UART_init();
void Keypad();

unsigned long Key;

//ROW PINS - GPIO0, GPIO1, GPIO2, GPIO3
//COLUMN PINS - GPIO4, GPIO5, GPIO6, GPIO7

void main(void)
{
    tiva_init();    //Initialization Function

    while(1){

    Cout_Rin_init();
    UART_init();
    Keypad();

    }
}



void tiva_init(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);   //set the clock frequency to 40MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);    //ROWS & COLUMN Interfacing
}

void Cout_Rin_init(){
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,C1|C2|C3|C4);     // Configuring Column pins as output pins
    GPIOPinWrite(GPIO_PORTB_BASE,C1|C2|C3|C4, 0x00);        // Providing Column pins with 0 Value C1:C4 = 0000
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,R1|R2|R3|R4);      // Configuring Row pins as Input pins
    GPIOPadConfigSet(GPIO_PORTB_BASE,R1|R2|R3|R4,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);  //providing Pull-up Configuration for Row pins R1:R4 = 1111
}

void Cin_Rout_init(){
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,R1|R2|R3|R4);     //Configure Row pins as Output
    GPIOPinWrite(GPIO_PORTB_BASE,R1|R2|R3|R4, 0x00);        // Providing row pins with 0 value R1:R4 = 0000
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,C1|C2|C3|C4);      //Configuring Column pins as input pins
    GPIOPadConfigSet(GPIO_PORTB_BASE,C1|C2|C3|C4,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU); // providing Pull-up configuration for Column pins C1:C4 = 1111
}

void UART_init(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// ENABLE GPIO PORT A,FOR UART
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);    //COLUMNS
    GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX
    GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 9600, 16000000);
}

    void Keypad(){
    Key = GPIOPinRead(GPIO_PORTB_BASE,R1|R2|R3|R4);

    if (Key == 0X0E){                                   // CASE 1 i.e. If a Key is pressed in ROW 1
        SysCtlDelay(666666);
        Cin_Rout_init();
        Key = GPIOPinRead(GPIO_PORTB_BASE,C1|C2|C3|C4); // Read all the Column pins to check which particular switch in ROW 1 was pressed

            if(Key == 0XE0){            //Key 1
                        SysCtlDelay(666666);
                        UARTprintf("1");

            }
            else if(Key == 0XD0){       //Key 2
                        SysCtlDelay(666666);
                        UARTprintf("2");

            }

            else if(Key == 0XB0){       //Key 3
                        SysCtlDelay(666666);
                        UARTprintf("3");

            }

            else if(Key == 0X70){       //Key 4
                        SysCtlDelay(666666);
                        UARTprintf("A");
            }
            SysCtlDelay(13333333);

        }
    if(Key == 0x0D){
        SysCtlDelay(666666);
        Cin_Rout_init();
        Key = GPIOPinRead(GPIO_PORTB_BASE, C1|C2|C3|C4);

        if(Key == 0xE0){
            SysCtlDelay(666666);
            UARTprintf("4");

        }
        else if(Key == 0xD0){
            SysCtlDelay(666666);
            UARTprintf("5");

        }
        else if(Key == 0xB0){
            SysCtlDelay(666666);
            UARTprintf("6");
        }
        else if(Key == 0x70){
            SysCtlDelay(666666);
            UARTprintf("B");
        }
        SysCtlDelay(13333333);
    }
    if(Key == 0x0B){
        SysCtlDelay(666666);
        Cin_Rout_init();
        Key = GPIOPinRead(GPIO_PORTB_BASE, C1|C2|C3|C4);

        if(Key == 0xE0){
            SysCtlDelay(666666);
            UARTprintf("7");

        }
        else if(Key == 0xD0){
            SysCtlDelay(666666);
            UARTprintf("8");

        }
        else if(Key == 0xB0){
            SysCtlDelay(666666);
            UARTprintf("9");
        }
        else if(Key == 0x70){
            SysCtlDelay(666666);
            UARTprintf("C");
        }
        SysCtlDelay(13333333);
    }
    if(Key == 0x07){
        SysCtlDelay(666666);
        Cin_Rout_init();
        Key = GPIOPinRead(GPIO_PORTB_BASE, C1|C2|C3|C4);

        if(Key == 0xE0){
            SysCtlDelay(666666);
            UARTprintf("*");
        }
        else if(Key == 0xD0){
            SysCtlDelay(666666);
            UARTprintf("0");

        }
        else if(Key == 0xB0){
            SysCtlDelay(666666);
            UARTprintf("#");
        }
        else if(Key == 0x70){
            SysCtlDelay(666666);
            UARTprintf("D");
        }
        SysCtlDelay(13333333);
    }
}


