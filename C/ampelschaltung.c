/*
Traffic lights simulation
Red light: pin B0
Yellow light: pin B1
Green light: pin B2
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>

#define TOGGLE_BIT(PORT,BIT) PORT^=(1<<BIT)

void setup(void){
	//make DDB0-DDB2 outputs
	DDRB |= 0b000111;
	//output DDB0-DDB2 low
	PORTB &= ~(0b000111);		
}

void loop(void){
	while(1){
		TOGGLE_BIT(DDRB,DDB0); //turn ON RED
		_delay_ms(1000);
		TOGGLE_BIT(DDRB,DDB1); //turn ON YELLOW
		_delay_ms(100);
		TOGGLE_BIT(DDRB,DDB0);
		TOGGLE_BIT(DDRB,DDB1); //turn OFF RED & YELLOW 
		TOGGLE_BIT(DDRB,DDB2); //turn ON GREEN
		_delay_ms(1000);
		TOGGLE_BIT(DDRB,DDB2); //turn OFF GREEN
		TOGGLE_BIT(DDRB,DDB1); //turn ON YELLOW
		_delay_ms(100);
		TOGGLE_BIT(DDRB,DDB1); //turn OFF YELLOW		
	}
}
int main(void)
{
	void setup();
    void loop();
}

