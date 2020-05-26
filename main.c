#include <avr/io.h>
#define  __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
void buzzer(int hz, int count);
#include <stdlib.h>
#include <stdio.h>
#define DHT11_PIN 4
uint8_t c = 0, Humi_I, Humi_D, Temp_I, Temp_D, checkSum;

void PJtime();
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD__INIT(void);
char String(char Data[]);
void MOVE(int x, int y);
void temp();
void Request();
uint8_t Receive_Data();
void Response();
#include <avr/io.h>
#include <util/delay.h>

typedef enum {false, true}bool;
void debugMsg(char *msg, char charLcd_yPos, bool b_lcd_init);

char str[10] = {0, };

int get_value(void)
{
	ADMUX =  0b11000011;    //use AREF, PORTF.3에 CDS 센서 연결됨.
	ADCSRA = 0b11100111;    //7번비트: ADC enable, 6번비트: ADC start,
	//5번비트:ADC free running,
	//2, 1, 0번 비트 111: prescaler 128로 셋팅함.
	//10비트 연속 변환모드의 정상 수행을 위해
	//50~200KHz 범위 이내여야함.
	
	while(ADCSRA&(1 << ADIF) == 0); // (ADIF비트 0될때까지)변환완료 될 때까지 대기
	
	return ADCL|(ADCH<<8); // return ADCW; // ADC값 반환
}

int Timer_Initial(){
	TCCR1A = (1<<COM1A1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12)|(1<<CS11)|(1<<CS10);
	ICR1 = 4999; // PWM = fclk_i/o / N(1+TOP)
	OCR1A = 375;
	TCNT1 = 0x00;
}

#define TRIG 6
#define ECHO 7
#define  SOUND_VELOCITY 340UL
char wa[8]={'0','0',':','0','0',':','0','0'};
char alarm[4] = {0,};
int flog = 1;
int sendsorValue = 0;
int main (void)
{
	scanf(&alarm);
	
	int i;
	DDRF = 0x00;
	DDRA |= 0x10;
	DDRD = 0x00;
	DDRB=0xFF;
	DDRG=0x0f;
	
	DDRE = 0x00;
	DDRC = 0xff;
	PORTC = 0x00;
	
	
	DDRF |= 0x10;
	Timer_Initial();
	unsigned int distance;
	DDRE = (DDRE | (1<<TRIG) & ~(1<<ECHO));
	
	LCD__INIT();
	MOVE(7,1);
	String("time");
	String("");
	MOVE(5,2);
	String("00:00:00");
	
	
	while(1){
		temp();
		TCCR3B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		PORTE |= (1<<TRIG);
		_delay_us(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE&(1<<ECHO)));
		TCNT3 = 0x0000;
		while(PINE & (1<<ECHO));
		TCCR3B = 0x00;
		distance = (unsigned)(SOUND_VELOCITY * (TCNT3 * 4 / 2) / 1000);
		
		
		MOVE(5,2);
		String(wa);
		String("    ");
		PJtime();
		
		if (wa[4]==alarm[3]&&wa[3]==alarm[2]&&wa[1]==alarm[1]&&wa[0]==alarm[0]&&flog==1)
		{
			while(1){
				temp();
				TCCR3B = 0x03;
				PORTE &= ~(1<<TRIG);
				_delay_us(10);
				PORTE |= (1<<TRIG);
				_delay_us(10);
				PORTE &= ~(1<<TRIG);
				while(!(PINE&(1<<ECHO)));
				TCNT3 = 0x0000;
				while(PINE & (1<<ECHO));
				TCCR3B = 0x00;
				distance = (unsigned)(SOUND_VELOCITY * (TCNT3 * 4 / 2) / 1000);
				
				if(distance < 500) {
					flog = 0;
					break;
				}
				for (i=0; i<20; i++)
				{
					buzzer(1047,10);
					buzzer(1319,10);
				}
				
				MOVE(5,2);
				String(wa);
				PJtime();
			}
		}
		
	}
}

void temp(){
	_delay_ms(200);
	sendsorValue = get_value();
	if (sendsorValue < 150)
	{
		PORTB =0x40;
	}else if (sendsorValue < 200)
	{
		PORTB =0x20;
	}else if (sendsorValue < 300)
	{
		PORTB =0x20;
	}else if (sendsorValue < 400)
	{
		PORTB =0x20;
	}else if (sendsorValue < 500)
	{
		PORTB =0xc0;
		}
	else{
		PORTB=0xc0;
	}
}

void PJtime(){
	_delay_ms(1000);
	wa[7]++;
	if(wa[7]>57)
	{
		wa[7]=48;
		wa[6]++;
		if(wa[6]>53)
		{	flog==1;
			wa[4]++;
			wa[6]=48;
			if(wa[4]>57)
			{	
				wa[3]++;
				wa[4]=48;
				if(wa[3]>53)
				{
					wa[1]++;
					wa[3]=48;
					if(wa[1]>57)
					{
						wa[0]++;
						wa[1]=48;
					}
				}
			}
			
		}
	}
}

void Request(){
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);		/* set to low pin */
	_delay_ms(18);					/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);		/* set to high pin */
}

void Response(){
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_Data(){
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);	/* check received bit 0 or 1 */
		_delay_us(35);
		if(PIND & (1<<DHT11_PIN))				/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);						/* then its logic HIGH */
		else									/* otherwise its logic LOW */
		c = (c<<1)|(0x00);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

void MOVE(int x, int y){
	unsigned char data;
	data = 0x80+x-1;
	if(y==2){
		data = 0xc0+x-1;
	}
	COMMAND(data);
}

void COMMAND(unsigned char byte){
	_delay_ms(2);
	PORTC = (byte & 0xF0);
	PORTC &= 0xFE;
	PORTC &= 0xFD;
	_delay_us(1);
	PORTC |= 0x04;
	_delay_us(1);
	PORTC &= 0xFB;
	
	PORTC = ((byte<<4) & 0xF0);
	PORTC &= 0xFE;
	PORTC &= 0xFD;
	_delay_us(1);
	PORTC |= 0x04;
	_delay_us(1);
	PORTC &= 0xFB;
}

char String(char Data[]){
	for(int i=0; Data[i]!=0; i++){
		DATA(Data[i]);
	}
}

void DATA(unsigned char byte)
{
	_delay_ms(2);
	// 데이터 상위 바이트
	PORTC = (byte & 0xF0);    // 데이터
	PORTC |= 0x01;        //RS = 1;
	PORTC &= 0xFD;        //RW = 0;
	_delay_us(1);
	PORTC |= 0x04;        //E = 1;
	_delay_us(1);
	PORTC &= 0xFB;        //E = 0;
	
	// 데이터 하위 바이트
	PORTC = ((byte<<4) & 0xF0);      // 데이터
	PORTC |= 0x01;        //RS = 1;
	PORTC &= 0xFD;        //RW = 0;
	_delay_us(1);
	PORTC |= 0x04;        //E = 1;
	_delay_us(1);
	PORTC &= 0xFB;        //E = 0;
}

void LCD__INIT(void)
{
	// 충분한 지연시간을 통한 안정화 과정
	_delay_ms(30);
	COMMAND(0x20);    // D5=1
	_delay_ms(39);
	COMMAND(0x20);    // D5=1
	_delay_ms(1.53);
	COMMAND(0x20);    // D5=1
	
	// 초기화 과정
	COMMAND(0x28);    // function set
	COMMAND(0x06);    // entry mode set
	COMMAND(0x01);    // all clear
	COMMAND(0x0c);    // display on
}

void buzzer(int hz, int count){
	int i,us;
	
	for(i=0; i<count; i++){
		us = (1000UL*1000)/hz/2;
		PORTA |= 1<<4;
		_delay_us(us);
		PORTA &= ~(1<<4);
		_delay_us(us);
	}
}
