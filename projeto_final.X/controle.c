//#include <pic18f4520.h>
//#include "config.h"
//#include "bits.h"
//#include "atraso.h"
//#include "lcd.h"
//#include "serial.h"
//#include "controle.h"
//#include "ssd.h"
//
//#include "bits.h"
//#include "lcd2.h"
//
//#include "keypad.h"
//
//
//
//#define L0 0x80
//#define L1 0xC0
//#define CLR 0x01
//#define ON 0x0F
//
//
//
//void main(void) {
//    
//    unsigned int tecla = 16;
//    unsigned char marcha='1';
//    unsigned long int cont=0;
//    float tempo;
//    lcdInit();
//    kpInit();
//    lcdCommand(ON);
//
//    
//    
//    
//    for(;;){
//            kpDebounce();
//            if (kpRead() != tecla){
//                tecla = kpRead();
//                if (bitTst(tecla, 3)) {cont = cont-360000; marcha='2';} 
//                if (bitTst(tecla, 7)) {cont = cont+360000;marcha='1';} 
//                if (bitTst(tecla, 2)) {cont = cont-6000;marcha='4';} 
//                if (bitTst(tecla, 6)) {cont = cont+6000;marcha='3';} 
//                if (bitTst(tecla, 1)) {cont = cont-100;marcha='R';} 
//                if (bitTst(tecla, 5)) {cont = cont+100;marcha='5';}
//                
//               
//           }
//            lcdPosition(0,0);
//            lcdData('M');
//            lcdData('a');
//            lcdData('r');
//            lcdData('c');
//            lcdData('h');
//            lcdData('a');
//            lcdData(':');
//            lcdData(' ');
//            lcdData(marcha);
//            
//            lcdPosition(1,0);
//            lcdData('v');
//            lcdData('l');
//            lcdData('o');
//            lcdData('c');
//            lcdData('i');
//            lcdData('d');
//            lcdData('e');
//            lcdData(':');
//            lcdData(' ');
//            lcdData(marcha);
//            
//    }
//}
//
//
//
//


#include <pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "atraso.h"
#include "lcd2.h"
#include "serial.h"
#include "controle.h"
#include "ssd.h"

//void EscreverMensagem(const char* str){
//
//    TRISA = 0xC3;
//    TRISB = 0x03;
//    TRISC = 0x01;
//    TRISD = 0x00;
//    TRISE = 0x00;
//    ADCON1 = 0x06;
//
//    lcdInit();
//
//
//    TRISCbits.TRISC7 = 1; //RX
//    TRISCbits.TRISC6 = 0; //TX
//
//    PORTB = 0;
//    
//    
//    lcd_str(str);
//    
//}


void NumeroDisplay7S(char numero, char posicao){
    ssdInit();
    ssdDigit(numero, posicao);
    ssdUpdate();   
}


