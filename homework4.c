#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework4.h"

state temp = base;
char prevChar;

int main(void)
{
    char rChar = '\0';
    char *response = "\n\n\r2534 is the best course in the curriculum!\r\n\n";
    // TODO: Declare the variables that main uses to interact with your state machine.
    int i = 0;
    char temp = '\0';
    // Stops the Watchdog timer.
    initBoard();
    // TODO: Declare a UART config struct as defined in uart.h.
    //       To begin, configure the UART for 9600 baud, 8-bit payload (LSB first), no parity, 1 stop bit.
    const eUSCI_UART_Config uartConfig = {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK, 19, 8, 0,
            EUSCI_A_UART_NO_PARITY,
            EUSCI_A_UART_LSB_FIRST,
            EUSCI_A_UART_ONE_STOP_BIT,
            EUSCI_A_UART_MODE,
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION };

    // TODO: Make sure Tx AND Rx pins of EUSCI_A0 work for UART and not as regular GPIO pins.
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2,
    GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN3,
    GPIO_PRIMARY_MODULE_FUNCTION);

    // TODO: Initialize EUSCI_A0
    UART_initModule(EUSCI_A0_BASE, &uartConfig);

    // TODO: Enable EUSCI_A0
    UART_enableModule(EUSCI_A0_BASE);

    while (1)
    {
        // TODO: Check the receive interrupt flag to see if a received character is available.
        //       Return 0xFF if no character is available.
        if (UART_getInterruptStatus(EUSCI_A0_BASE,
        EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) == 1)
        {
            prevChar = temp;
            rChar = UART_receiveData(EUSCI_A0_BASE);
            temp = rChar;

        }
        else
        {
            rChar = 0xFF;
        }

        // TODO: If an actual character was received, echo the character to the terminal AND use it to update the FSM.
        //       Check the transmit interrupt flag prior to transmitting the character.
        if (rChar != 0xFF)
        {
            while (UART_getInterruptStatus( EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)==0){};
                UART_transmitData(EUSCI_A0_BASE, rChar);
        }

        // TODO: If the FSM indicates a successful string entry, transmit the response string.
        //       Check the transmit interrupt flag prior to transmitting each character and moving on to the next one.
        //       Make sure to reset the success variable after transmission.

        if (charFSM(rChar))
        {
            int i = 0;
            while (*(response + i) != '\0')
            {
                while (UART_getInterruptStatus( EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)==0){};
                UART_transmitData(EUSCI_A0_BASE, *(response + i));
                i++;
            }
        }
    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: FSM for detecting character sequence.
bool charFSM(char rChar)
{
    bool finished = false;
    if (rChar != 0xFF)
    {
        if (rChar == '2')
        {
            if (temp == base)
                temp = state_1;
            else
                temp = state_1;
        }
        else if (temp == state_1)
        {
            if (prevChar == '2' && rChar == '5')
                temp = state_2;
            else
                temp = base;
        }
        else if (temp == state_2)
        {
            if (prevChar == '5' && rChar == '3')
                temp = state_3;
            else
                temp = base;
        }
        else if (temp == state_3)
        {
            if (prevChar == '3' && rChar == '4')
                finished = true;

            temp = base;
        }
    }

    return finished;
}
