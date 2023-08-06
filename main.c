#define F_CPU 16000000UL
#include <avr/io.h> //standard AVR header
#include <util/delay.h> //delay header

#define LCD_DPRT PORTD //LCD DATA PORT
#define LCD_DDDR DDRD //LCD DATA DDR
#define LCD_DPIN PIND //LCD DATA PIN

#define LCD_CPRT PORTB //LCD COMMANDS PORT
#define LCD_CDDR DDRB //LCD COMMANDS DDR
#define LCD_CPIN PINB //LCD COMMANDS PIN

#define LCD_RS 0 //LCD RS connects to PORTB.0
#define LCD_RW 1 //LCD RW connects to PORTB.1
#define LCD_EN 3 //LCD EN connects to PORTB.3

void lcdCommand( unsigned char cmnd )
{
  // D4 connects to PORTD.4
  // D5 connects to PORTD.5
  // D6 connects to PORTD.6
  // D7 connects to PORTD.7
  // BLA connects to +ve with resister
  // BLK connects to -ve
  // VO connects to potentiameter
  // VDD connects to +ve
  // GND connects to -ve
  // +ve connects to 5V arduino port
  // -ve connects to random GND port on arduino
	LCD_DPRT = cmnd & 0xF0; //send high nibble to D4-D7
	LCD_CPRT &= ~ (1<<LCD_RS); //RS = 0 for command
	LCD_CPRT &= ~ (1<<LCD_RW); //RW = 0 for write
	LCD_CPRT |= (1<<LCD_EN); //EN = 1 for H-to-L pulse
	_delay_us(1); //make EN pulse wider
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	_delay_us(100); //wait
	LCD_DPRT = cmnd<<4; //send low nibble to D4-D7
	LCD_CPRT |= (1<<LCD_EN); //EN = 1 for H-to-L pulse
	_delay_us(1); //make EN pulse wider
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	_delay_us(100); //wait
}
void lcdData( unsigned char data )
{
	LCD_DPRT = data & 0xF0; //send high nibble to D4-D7
	LCD_CPRT |= (1<<LCD_RS); //RS = 1 for data
	LCD_CPRT &= ~ (1<<LCD_RW); //RW = 0 for write
	LCD_CPRT |= (1<<LCD_EN); //EN = 1 for H-to-L pulse
	_delay_us(1); //make EN pulse wider
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	LCD_DPRT = data<<4; //send low nibble to D4-D7
	LCD_CPRT |= (1<<LCD_EN); //EN = 1 for H-to-L pulse


	_delay_us(1); //make EN pulse wider
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	_delay_us(100); //wait
}
void lcd_init()
{
	LCD_DDDR = 0xFF;
	LCD_CDDR = 0xFF;
	LCD_CPRT &=~(1<<LCD_EN); //LCD_EN = 0
	lcdCommand(0x33); //send $33 for init.
	lcdCommand(0x32); //send $32 for init.
	lcdCommand(0x28); //init. LCD 2 line,5×7 matrix
	lcdCommand(0x0e); //display on, cursor on
	lcdCommand(0x01); //clear LCD
	_delay_us(2000);
	lcdCommand(0x06); //shift cursor right
}
void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char firstCharAdr[]={0x80,0xC0,0x94,0xD4};
	lcdCommand(firstCharAdr[y-1] + x - 1);
	_delay_us(100);
}
void lcd_print(char * str )
{
	unsigned char i = 0;
	while(str[i]!=0)
	{
		lcdData(str[i]);
		i++ ;
	}
}
int main(void)
{
	lcd_init();
	lcd_gotoxy(1,1);
	lcd_print("Hello World!");
	//lcd_gotoxy(1,2);
	//lcd_print("one country");
	while(1); //stay here forever
	return 0;
}
