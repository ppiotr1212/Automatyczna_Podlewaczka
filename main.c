#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define C_LED_OFF (0<<PC2) 
#define B_LED_OFF (0<<PC1)
#define A_LED_OFF (0<<PC0)
#define C_LED_ON (1<<PC2) 
#define B_LED_ON (1<<PC1)
#define A_LED_ON (1<<PC0)

#define SIL_ON (1<<PC3)
#define SIL_OFF (0<<PC3)

uint16_t pomiaro( uint8_t pin);


int main (void)
{
	
	ADCSRA |= ( 1 << ADEN );
	ADCSRA |= ( 1 << ADPS2 ); 
	ADMUX |= ( 1 << REFS0 ); 

	uint16_t wyniko = 0;
	uint16_t wynikw = 0;
	int zalaczony = 0;
	DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3); 
	DDRC &= ~(1<<PC5)| (1<<PC4); 

	PORTC |= A_LED_OFF | B_LED_OFF | C_LED_OFF; 

	while(1)
	{

		wyniko = pomiaro( PC5 ); 
		wynikw = pomiaro( PC4 ); 
		_delay_ms( 50 );
		PORTC = A_LED_OFF | B_LED_OFF | C_LED_OFF; 

		if (wyniko > 600)
			{
					PORTC |= A_LED_ON; 
			}
		if (wyniko > 400 && wyniko <=600)
				{
							PORTC |= B_LED_ON; 
					}
		if (wyniko <400)
				{

							if(wynikw > 700){
								PORTC |= SIL_ON;
								_delay_ms( 4000 );
								PORTC &= SIL_OFF;
								PORTC |= C_LED_ON | A_LED_ON | B_LED_ON;
								_delay_ms( 4000 );

				}else {
					PORTC |= C_LED_ON; 
				}


}}}

uint16_t pomiaro( uint8_t pin) 
{
	ADMUX = ( ADMUX & 0b11111000 ) | pin;

	ADCSRA |= ( 1 << ADSC ); 

	while( ADCSRA & ( 1 << ADSC ));

	return ADCW;

}


