/*
 * TP1entregable.c
 *
 * Created: 4/4/2022 14:15:44
 * Author : Victor
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL // Defino la frecuencia de oscilador en 8MHz
#include <util/delay.h>

char puls() { /* Función para detectar correctamente al pulsador*/
	if ((PINC & (1<<PINC0))== 0) {
		_delay_ms(20);
		while((PINC & (1<<PINC0)) == 0); //Pausa  la ejecucion mientras el pulsador este presionado
		_delay_ms(20);
		return 1;
	} 
	else
		return 0;
}


int main(void) {
	signed char i=3; /* Declaro indice */
	unsigned char vec1[4]={0x81, 0x42, 0x24, 0x18}; /* Declaración de arreglo correspondiente a la secuencia */
	/*
	0x01=0b00000001 - LED0: LED Verde
	0x02=0b00000010 - LED1: LED Verde
	0x04=0b00000100 - LED2: LED Rojo
	0x08=0b00001000 - LED3: LED Rojo
	0x10=0b00010000 - LED4: LED Azul
	0x20=0b00100000 - LED5: LED Azul
	0x40=0b01000000 - LED6: LED Amarillo
	0x80=0b10000000 - LED7: LED Amarillo
	
	0x81 - LED Verde y LED Amarillo
	0x42 - LED Verde y LED Amarillo
	0x24 - LED Rojo y LED Azul
	0x18 - LED Rojo y LED Azul
	*/	
	DDRB = 0xFF;
	DDRC = 0xFE; 	// Se asigna el valor 0b11111110 en hexadecimal al puerto C de Data Direction Register. Lo que hace es asignar el bit 0 como entrada.
	PORTC = 1<<PINC0; 	//Se asigna 1 al bit 0 Puerto C del Data Register.
	//Las anteriores 2 instrucciones configuran el pin PC0 con pull-up. Usara la resistencia interna de pull-up.

	while(1){
		while(!puls())
		{
				i++;
				if (i==4) {
					i=0;
				}
				PORTB = vec1[i]; /* Pongo en PORTB el valor del arreglo en la posición i */
				_delay_ms(100);
		}
		while(!puls())
		{
			i--;
			if (i==-1) {
				i=3;
			}
			PORTB = vec1[i]; /* Pongo en PORTB el valor del arreglo en la posición i */
			_delay_ms(100);
		}
		} /* Fin del loop infinito */
		return 0;
	}
