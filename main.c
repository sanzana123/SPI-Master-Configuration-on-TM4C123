#include <stdbool.h>
#include <stdint.h>
#include "clock.h"
#include "wait.h"
#include "tm4c123gh6pm.h"

#define portA_Spi_pins 0x3C

/**
 * main.c
 */

//Configuration for SSI0 Module as a Master

void initSPI()
{

    SYSCLK_RCGCSSI_R |= SYSCLK_RCGCSSI_R0; //Enabling the clock for SSI0
    SYSCLK_RCGCGPIO_R |= SYSCLK_RCGCGPIO_R0;   //Enabling the clock for GPIO PortA //Port A

    GPIO_PORTA_AFSEL_R = GPIO_PORTA_AFSEL_R | portA_Spi_pins; //Telling PA2, PA3, PA4, PA5 to act as another peripheral
    GPIO_PORTA_PCTL_R &= ~(0x00FFFF00);   //Clearing the PCTL register
    GPIO_PORTA_PCTL_R |= 0x00222200;      //Configuring the PCTL register to have a 0x2 because that would help the GPIO Pins PA
                                          //PA2 to work as SSIClk, PA3 to work as SSIFss, PA4 to work as SSITx, PA5 to work as SSIRx
    GPIO_PORTA_DEN_R = GPIO_PORTA_DEN_R | portA_Spi_pins; //Enabling the digital enable pin PA2, PA3, PA4, PA5

    SSI0_CR1_R &= ~(SSI_SSE); //Clearing the SSE bit

    //SSI0_CR1_R =  0x0000.0000; //ssi0 has been set as a master

    SSI0_CC_R = 0x00; //use the system clock

    SSI0_CPSR_R |= 0x00000002; //CPSR= Clock prescaler divisor always 0x2

    //Using formula:
    //Spi clock = (System clock) / (CSPR *(1+SCR))
    SSI0_CR0_R |=  0x000009C7; //CR0: Data size = 8 Bits, Frame rate = Freescale SPI, Serial Clock and Polarity = 1, SCR = 0x9

    SSI0_CR1_R |= SSI_SSE; //Setting the SSE Bit
}

void SSI_send_data(uint8_t data)
{
    //SR is the Status Register, TNF = Transmit Fifo is not full
    while ((SSI0_SR_R & SSI_TNF)==0); //Wait until the transmit fifo has space to write to
    SSI0_DATA_R = data;

}

void SSI_read_data()
{
    while ((SSI0_SR_R & SSI_RFF)==0);

    uint8_t data = SSI0_DR_R;

}

int main(void)
{
    initSystemClckTo20Mz();
    initSPI();

    char c = 'P';
    SSI_send_data(c);
	return 0;
}
