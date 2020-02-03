/*	Partner(s) Name & E-mail: David Wilson
 *	Lab Section: 023
 *	Assignment: Lab #7  Exercise #1 
 *	Exercise Description: [optional - include for your own benefit]
 *	
 *	I acknowledge all content contained herein, excluding template 
 * 	or example code, is my own original work.
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"

volatile unsigned char TimerFlag=0;

unsigned long _avr_timer_M =1;
unsigned long _avr_timer_cntcurr=0;
unsigned char tmpA = 0x00;
unsigned char tmpC =0x00;


void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A= 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
	void TimerOff()
	{
	TCCR1B= 0x00;	
	}
	
	void TimerISR()
	{
		TimerFlag = 1;
	}
	ISR(TIMER1_COMPA_vect)
	{
		_avr_timer_cntcurr--;
		if (_avr_timer_cntcurr==0)
		{
			TimerISR();
			_avr_timer_cntcurr=_avr_timer_M;
		}
	}
	voidTimerSet(unsigned long M)
	{
		_avr_timer_M=M;
		_avr_timer_cntcurr=_avr_timer_M;
	}
}

enum States(Hold,Decrease, Increase, Reset)state;

unsigned char button1;
unsigned char button2;

unsigned char tmpC;

void Tick()
{
	button1 = ~PINA=0x00;
	button2 = ~PINB= 0x00;
	
	case Hold:
		if(button1 && !button2)
		{
			state=Increase;
		}
	else if(button1&& button2)
	{
		state=Reset;
	}
	else if(!button1 && button2)
	{
		state = Decrease;
	}
	else
	{
		state=Hold;
	}
	break;
}


	case Increase:
	if(button1 && !button2)
	{
		state=Increase;
	}
	else if(button1&& button2)
	{
		state=Reset;
	}
	else 
	{
		state=Hold;
	}
	break;
}

	case Decrease:
	if(!button1 && button2)
	{
		state = Decrease;
	}

		else if(button1&& button2)
		{
			state=Reset;
		}
		else
		{
			state=Hold;
		}
	break;
	}
	case Reset:
	if (button1 && button2)
	{
		state=Reset;
	}
	else
	{
		state=Hold;
	}
	break;

}
switch(state)
{
	case Hold:
	break;
	
	case Increase:
	
	if(tmpC<9)
	{
	tmpC=tmpC+1;	
	}	
	break;
	
	case Decrease:
	if(tmpC > 0)
	tmpC = tmpC - 1;
	break;
	
	case Reset:
	tmpC = 0;
	break;
	
	
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // A input initialize to 0xFF
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTD = 0x00; // LCD control lines

	TimerSet(1000);
	TimerOn();
	
	// Initializes the LCD display
	LCD_init();
	LCD_ClearScreen();
	
	state = Hold;
	tmpC = 0x00;
	while(1){
		LCD_Cursor(1);
		button_Tick();
		LCD_WriteData(tmpC + '0');
		while(!TimerFlag){}
		TimerFlag = 0;
    }

	
}


