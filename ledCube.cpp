
#define F_CPU 40000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#define RAND_MAX 0xff

int cnt = 0;

//инициализация прерываний
void intInit(){
	//сбрасываем все биты ISCxx, потому что прерывание по низкому уровню на PD2(INT0)
	MCUCR &= ~( (1<<ISC11)|(1<<ISC10)|(1<<ISC01)|(1<<ISC00) );
	//разрешаем внешнее прерывание INT0
	GICR |= (1<<INT0);
	//выставляем флаг глобального разрешения прерываний
	sei();	
}

//функция обработчик внешнего прерывания INT0
ISR( INT0_vect )
{
	while((PIND & (1<<PD2))==0);
	_delay_ms(50);
	cnt++;
	if(cnt>3)cnt=0;
}

void effectRandFast(){
	PORTA = rand();
	PORTC = rand();
	PORTB = rand();
	_delay_ms(10);
}

void effectRandSlow(){
	PORTA = rand();
	PORTC = rand();
	PORTB = rand();
	_delay_ms(100);
}

void effectVerticalSlide(){
	PORTB = 0x0f;
	PORTA = 0b00010001;
	PORTC = 0b00010001;
	_delay_ms(10);
	PORTA = 0b00100010;
	PORTC = 0b00100010;
	_delay_ms(10);
	PORTA = 0b01000100;
	PORTC = 0b01000100;
	_delay_ms(10);
	PORTA = 0b10001000;
	PORTC = 0b10001000;
	_delay_ms(10);
	PORTA = 0b01000100;
	PORTC = 0b01000100;
	_delay_ms(10);
	PORTA = 0b00100010;
	PORTC = 0b00100010;
	_delay_ms(10);
}

void effectHorizontalSlide(){
	PORTB = 0x0f;
	PORTC = 0x00;
	PORTA = 0x0f;
	_delay_ms(10);
	PORTA = 0xf0;
	_delay_ms(10);
	PORTC = 0xf0;
	PORTA = 0x00;
	_delay_ms(10);
	PORTC = 0x0f;
	_delay_ms(10);
	PORTC = 0xf0;
	_delay_ms(10);
	PORTC = 0x00;
	PORTA = 0xf0;
	_delay_ms(10);
}

void effectDownToUpSlide(){
	PORTA = 0xff;
	PORTC = 0xff;
	PORTB = 0b0000001;
	_delay_ms(10);
	PORTB = 0b0000010;
	_delay_ms(10);
	PORTB = 0b0000100;
	_delay_ms(10);
	PORTB = 0b0001000;
	_delay_ms(10);
	PORTB = 0b0000100;
	_delay_ms(10);
	PORTB = 0b0000010;
	_delay_ms(10);
}

void effectRain(){
	PORTB = 0b00000001;
	PORTA = rand();
	PORTC = rand();
	_delay_ms(50);
	PORTB = 0b00000010;
	PORTA = rand();
	PORTC = rand();
	_delay_ms(50);
	PORTB = 0b00000100;
	PORTA = rand();
	PORTC = rand();
	_delay_ms(50);
	PORTB = 0b00001000;
	PORTA = rand();
	PORTC = rand();
	_delay_ms(50);	
}

int main(void)
{	
	//настраиваем выводы анодов	
	DDRA = 0xff;
	PORTA = 0x00;
	
	DDRC = 0xff;
	PORTC = 0x00;
	
	//настраиваем выводы катодов
	DDRB = 0x0f;
	PORTB = 0x0f;
	
	//кнопка
	DDRD = 0x00;
	PORTD = 0b00000100;
	
	//инициализация прерывания INT0
	intInit();
	
    while(1)
    {
    		//переключение эффектов
    		switch(cnt){
    			case 0:effectRandFast();
    				   break;
    			case 1:effectRandSlow();
    				   break;
    			case 2:effectHorizontalSlide();
    				   effectDownToUpSlide();
    				   effectVerticalSlide();
    				   break;
    			case 3:effectRain();
    			       break;
    		}
    }
}
