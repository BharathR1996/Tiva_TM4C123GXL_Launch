#include<stdint.h>
#include<stdbool.h>

#include"Uart_lib.h"

//void uartint(void);

//unsigned char data;

int main(void)
{

Uart_Init();

Uart_Initial_Connect();

while (1)
    {
        Uart_data_verify();
    }

}
