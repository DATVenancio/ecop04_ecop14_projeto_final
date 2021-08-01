/*
 Aluno:     Daniel Augusto Teixeira Venâncio
 Matrícula: 2020006079
 Turma:     ECOP04 - T01 / ECOP14 - T02
 
 */
#include "pic18f4520.h"
#include "config.h"
#include "bits.h"
#include "atraso.h"
#include "serial.h"
#include "controle.h"
#include "ssd.h"
#include "bits.h"
#include "lcd2.h"
#include "keypad.h"
#include "adc.h"
#include "i2c.h"
#include "pwm.h"

#define L0 0x80
#define L1 0xC0
#define CLR 0x01
#define ON 0x0F


void itoa(unsigned int val, char* str );

void main(void) {
    
    //variaveis
    unsigned char tmp;

    //controle da tecla precionada
    unsigned int tecla = 16;
    
    ////controle da marcha do carro
    unsigned char marcha='M';
    unsigned char ligado='0';

    //controle de gasolina
    float tempo=0;
    int abastecer=0;
    unsigned char gasolina1='1',gasolina2='4';
    
    //controle de seta
    unsigned char setaEsquerda='0',setaDireita='0';
    
    //mensagens
    
    
    lcdInit();
    kpInit();
    serial_init();
    pwmInit();

    TRISCbits.TRISC7 = 1; //RX
    TRISCbits.TRISC6 = 0; //TX
   
    
    
    lcdPosition(0,1);
    lcdMessage("ECOP04/ECOP14");
    lcdPosition(1,0);
    lcdMessage("Trabalho final");
    atraso_ms(5000);

    for(;;){
        
        
            TRISD=0x0F;
            TRISCbits.TRISC0 = 0;
            TRISEbits.TRISE0 = 0;

            kpDebounce();
            if (kpRead() != tecla){
                tecla = kpRead();
                if (bitTst(tecla, 3)) {marcha='2';pwmSet1(45);} 
                if (bitTst(tecla, 7)) {marcha='1';pwmSet1(32);} 
                if (bitTst(tecla, 2)) {marcha='4';pwmSet1(75);} 
                if (bitTst(tecla, 6)) {marcha='3';pwmSet1(64);} 
                if (bitTst(tecla, 1)) {marcha='R';pwmSet1(32);} 
                if (bitTst(tecla, 5)) {marcha='5';pwmSet1(96);}
                if (bitTst(tecla, 8)) {abastecer=1;}
                if (bitTst(tecla, 9)) {
                    lcdCommand(CLR);
                    if(ligado=='1'){
                        ligado='0';
                    }
                    else{
                        ligado='1';
                        marcha='M';
                    }
                }
                if (bitTst(tecla, 10)) {
                    if(ligado=='1'){
                       TRISCbits.TRISC0 = 0;
                        TRISEbits.TRISE0 = 0;

                        for (unsigned char i = 0; i < 5; i++) {
                            PORTCbits.RC0 ^= 1;
                            atraso_ms(500);
                        }
                        PORTCbits.RC0 = 0; 
                    }
                    
                }
                if (bitTst(tecla, 11)) {
                    if(ligado=='1'){
                        TRISCbits.TRISC0 = 0;
                        TRISEbits.TRISE0 = 0;

                        for (unsigned char i = 0; i < 5; i++) {
                            PORTEbits.RE0 ^= 1;
                            atraso_ms(500);
                        }
                        PORTEbits.RE0 = 0;
                    }
                    
                }
                
                
                
               
           }
            
            if(ligado=='1'){
                    lcdPosition(0,0);
                    lcdMessage("MARCHA : ");
                    lcdData(marcha);

                    lcdPosition(1,0);
                    lcdMessage("GASOLINA : ");
                    lcdData(gasolina1);
                    lcdData(gasolina2);                         
                    atraso_ms(10);


                    while(abastecer==1){

                        lcdCommand(CLR);
                        lcdPosition(0,0);
                        lcdMessage("ABASTECER : ");

                        //leitura serial para gasolina
                        tmp = serial_rx(2000);
                        //tmp=0xa5;
                        while(tmp==0xa5){
                            tmp = serial_rx(2000);
                        }
                        gasolina1=tmp;
                        lcdData(gasolina1);

                        tmp = serial_rx(2000);
                        tmp=0xa5;
                        while(tmp==0xa5){
                            tmp = serial_rx(2000);
                        }
                        gasolina2=tmp;
                        tmp=0xa5;
                        lcdData(gasolina2);
                        lcdData(' ');
                        lcdData('L');
                        atraso_ms(3000);



                        lcdCommand(CLR);
                        abastecer=0;
                    }
                    //definição de um tempo para gasto da gasolina
                    if(tempo==1000){
                        tempo=0;
                        if(gasolina2=='0'){
                            gasolina2='9';
                            gasolina1--;
                        }else{
                            gasolina2--;
                        }
    
                    }
                    tempo++;
                
            }else{
                pwmSet1(0);
                abastecer=0;
                marcha='M';
                PORTCbits.RC0 = 0;
                lcdPosition(0,0);
                lcdMessage("CARRO DESLIGADO : ");
                lcdPosition(1,0);
                lcdMessage("LIGA/DESLIGA : 9 ");
                atraso_ms(5);
                
            }
            
            
    }
}


void itoa(unsigned int val, char* str )
{
  str[0]=(val/10000)+0x30;  
  str[1]=((val%10000)/1000)+0x30;  
  str[2]=((val%1000)/100)+0x30;  
  str[3]=((val%100)/10)+0x30;
  str[4]=(val%10)+0x30;
  str[5]=0;
}
