/**
 *	Quick and very Dirty GPIO API.
 *
 **/

#include "gpio.h"

typedef struct {
	unsigned long	GPFSEL[6];	///< Function selection registers.
	unsigned long	Reserved_1;
	unsigned long	GPSET[2];
	unsigned long	Reserved_2;
	unsigned long	GPCLR[2];
	unsigned long	Reserved_3;
	unsigned long	GPLEV[2];
	unsigned long	Reserved_4;
	unsigned long	GPEDS[2];
	unsigned long	Reserved_5;
	unsigned long	GPREN[2];
	unsigned long	Reserved_6;
	unsigned long	GPFEN[2];
	unsigned long	Reserved_7;
	unsigned long	GPHEN[2];
	unsigned long	Reserved_8;
	unsigned long	GPLEN[2];
	unsigned long	Reserved_9;
	unsigned long	GPAREN[2];
	unsigned long	Reserved_A;
	unsigned long	GPAFEN[2];
	unsigned long	Reserved_B;
	unsigned long	GPPUD[1];
	unsigned long	GPPUDCLK[2];
	//Ignoring the reserved and test bytes
} BCM2835_GPIO_REGS;

volatile BCM2835_GPIO_REGS * const pRegs = (BCM2835_GPIO_REGS *) (0x20200000);


void SetGpioFunction(unsigned int pinNum, unsigned int funcNum) {

	int offset = pinNum / 10;

	unsigned long val = pRegs->GPFSEL[offset];	// Read in the original register value.

	int item = pinNum % 10;
	val &= ~(0x7 << (item * 3));
	val |= ((funcNum & 0x7) << (item * 3));
	pRegs->GPFSEL[offset] = val;
}

void SetGpio(unsigned int pinNum, unsigned int pinVal) {
	unsigned long mask=(1<<pinNum);

	if(pinVal) {
		*((unsigned long*)(pRegs->GPSET))|=mask;
	} else {
		*((unsigned long*)(pRegs->GPCLR))|=mask;
	}
}

void EnableGpioDetect(unsigned int pinNum, enum DETECT_TYPE type)
{
	unsigned long mask=(1<<pinNum);
	
	switch(type) {
	case DETECT_RISING:
		*((unsigned long*)(pRegs->GPREN))|=mask;
		break;
	case DETECT_FALLING:
		*((unsigned long*)(pRegs->GPFEN))|=mask;
		break;
	case DETECT_NONE:
	default:
		break;
	}
}

void DisableGpioDetect(unsigned int pinNum, enum DETECT_TYPE type)
{
	unsigned long mask=~(1<<pinNum);
	
	switch(type) {
	case DETECT_RISING:
		*((unsigned long*)(pRegs->GPREN))&=mask;
		break;
	case DETECT_FALLING:
		*((unsigned long*)(pRegs->GPFEN))&=mask;
		break;
	case DETECT_NONE:
	default:
		break;
	}
}

void ClearGpioInterrupt(unsigned int pinNum)
{
	unsigned long mask=(1<<pinNum);
	*((unsigned long*)(pRegs->GPEDS))=mask;
}
