#include <16f887.h>
#fuses INTRC_IO
#use delay(CLOCK=8MHz)
#include <lcd.c>
#define dw PIN_E0
#define up PIN_E1
#define set PIN_E2

void display(); 
void adjust();
void setup(); 
void check_day();
void check_setup();
int8 i, tt = 0;
signed int16 value[10] = {0,9,20,24,4,2023,0,0,0};// 0khac 1gio 2phut 3ngay 4thang 5nam 6thu 7giay
char thu[9][4]={{"Mon"},{"Tue"},{"Wed"},{"Thu"},{"Fri"},{"Sat"},{"Sun"}};

#int_timer1
void interrupt_timer1()
{ 
value[0]++; 
if(value[0] > 4){
value[0] -= 5;
   value[0] = 0;
   value[7]++;
   
   if(value[7]>59){
      value[7] = 0;
      value[2]++;
   
      if(value[2]>59){
         value[2] = 0;
         value[1]++;
      
         if(value[1]>23){
            value[1] = 0;
            check_day();
            value[6]++;
            if(value[6] > 6)
            value[6] = 0;
         
               if(value[4] > 12){
                  value[4] = 1;
                  value[5]++;
            }
         }
      }
   }
}
set_timer1(-50000); 
}

void main(){
   set_tris_e(0xff);
   lcd_init();
   setup_timer_1(t1_internal | t1_div_by_8); 
   set_timer1(-50000); 
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   while(TRUE){
      if(tt==0){
         adjust();
         display();
         }
      else{
         setup();
         adjust();
         }
      }
}

void display(){
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
}

void adjust(){
if(input(set)==0){
   delay_ms(50);
   if(tt<6)
      tt++;
   else
      tt = 0;
   while(input(set)==0);
      delay_ms(50);
   }

if(input(up)==0){
   delay_ms(50);
   value[tt]++;
   while(input(up) == 0);
      delay_ms(50);
}

if(input(dw)==0){
   delay_ms(50);
   value[tt]--;
   while(input(dw) == 0);
      delay_ms(50);
}
check_setup();
}


void setup(){
if(tt == 1){
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
      delay_ms(100);
      
      lcd_gotoxy(1,1);
      printf(lcd_putc,"  :%02ld:%02ld",value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
      delay_ms(100);
}
if(tt == 2){
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
      delay_ms(100);
      
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:  :%02ld",value[1],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
      delay_ms(100);
}
else if(tt == 3){
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"  /%2ld/%04ld",value[4],value[5]);
      delay_ms(100);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
      delay_ms(100);
   }
else if(tt == 4){
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/  /%04ld",value[3],value[5]);
      delay_ms(100);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
      delay_ms(100);
   }
else if(tt == 5){
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/    ",value[3],value[4]);
      delay_ms(100);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%04ld",value[3],value[4],value[5]);
      delay_ms(100);
   }
else if(tt == 6){
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      for(i = 0; i < 3; i++){
         lcd_gotoxy(10+i,1);
         printf(lcd_putc,"%c",thu[value[6]][i]);
         }
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%4ld",value[3],value[4],value[5]);
      delay_ms(100);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%02ld:%02ld:%02ld",value[1],value[2],value[7]);
      printf(lcd_putc,"        ");
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%2ld/%2ld/%4ld",value[3],value[4],value[5]);
      delay_ms(100);
}
else break;

if(tt < 7){
   adjust();
}
}

void check_day(){
if(value[4] == 2){
   if(value[5] % 4 == 0){
      if(value[3] < 29){
         value[3]++;
      }
      else{
         value[3] = 1;
         value[4]++;
         }
   }
   else if(value[3] < 28){
      value[3]++;
   }
        else{
           value[3] = 1;
           value[4]++;
            }
}

else if(value[4] < 8 && value[4]%2==1){
   if(value[3] < 31){
      value[3]++;
   }
   else{
      value[3] = 1;
      value[4]++;
      }
}
else if(value[4] < 8 && value[4]%2==0){
   if(value[3] < 30){
      value[3]++;
   }
   else{
      value[3] = 1;
      value[4]++;
      }
}
else if(value[4] > 8 && value[4]%2==1){
   if(value[3] < 30){
      value[3]++;
   }
   else{
      value[3] = 1;
      value[4]++;
      }
}
else if(value[4] > 8 && value[4]%2==0){
   if(value[3] < 31){
      value[3]++;
   }
   else{
      value[3] = 1;
      value[4]++;
      }
}
}

void check_setup(){
if(value[1]>23){
   value[1] = 0;
   }
if(value[1]<0){
   value[1] = 23;
   }
if(value[2]<0){
   value[2] = 59;
   }
if(value[2]>59){
   value[2] = 0;
   }
if(value[4]>12){
   value[4] = 1;
   }
if(value[4]==0){
   value[4]=12;
   }
if(value[6]>6){
   value[6] = 0;
   }
if(value[6]<0){
   value[6] = 6;
   }

if(value[4] == 2){
   if(value[5] % 4 == 0){
      if(value[3] > 29)
         value[3] = 1;
      if(value[3]==0)
         value[3]=29;
   }
   else {
      if(value[3] > 28){
         value[3] = 1;
          }
      if(value[3]==0){
         value[3] = 28;
      }
   }
}
else if(value[4] < 8 && value[4]%2==1){
   if(value[3] > 31){
      value[3]=1;
      }
   if(value[3]==0){
      value[3] = 31;
      }
}

else if(value[4] < 8 && value[4]%2==0){
   if(value[3] > 30){
      value[3] = 1;
      }
   if(value[3]==0){
      value[3] = 30;
      }
}
else if(value[4] > 8 && value[4]%2==1){
   if(value[3] > 30){
      value[3] = 1;
      }
   if(value[3]==0){
      value[3] = 30;
      }
}
else if(value[4] > 8 && value[4]%2==0){
   if(value[3] > 31){
      value[3] = 1;
      }
   if(value[3]==0){
      value[3] = 31;
   }
   }
}


