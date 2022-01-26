#include <18F4550.h>
#device ADC=10 

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)
#FUSES NOMCLR INTRC_IO  

#use delay(internal=8000000)

#include <lcd.c>
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)

int16 lecturadigital = 0;   // int16 lecturadigital;
int8 temp = 0;

void main()
{
   lcd_init(); 
   
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_8);
   
   while(TRUE)
   { 
    set_adc_channel(0); //Seleccionar Canal 0 para leer el pot
    delay_us(20);
    
    lecturadigital=read_adc();  // es una funcion que el valor analogico  y convertirlo a digital con un resolucion de 10 bits
    
    temp=(float)lecturadigital*500/1023;  // voltaje=(lecturadigital*5.0)/1023.0;
    
    printf("%u\n",temp); 
    lcd_gotoxy(1,1);
    
    if(temp<101 && temp>=0)
      printf(lcd_putc,"La temperatura \n es:   %u   C",temp);
    else
      printf(lcd_putc, "La Temperatura \n es invalida"); 
   }
LCD_PUTC("\f");
}

