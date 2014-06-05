/*---------------------------------------------------
	Battery.c (v1.00)
	
	µç³ØµçÁ¿ÅÐ¶Ï
---------------------------------------------------*/	

#include "main.h"
#include "port.h"

#include "Battery.h"
#include "voice.h"
#include "Delay.h"

/*------ public variable -----------------------------------*/
extern tByte key_rotated_on_flag;
extern bit BAT_Lowflag;

/*----------------------------------------------------
	verifybattery()
	voice alarm for battery status
-----------------------------------------------------*/

void verifybattery(tWord Check2)
	{	
	// battery is sufficient, battery > 53V, 4.82V/4.88V
	if((Check2 >= 0x3f3))
		{
		voice_EN = 1;
		SC_Speech(28);  	
		Delay(60);
		voice_EN = 0;
		}
   // 20km, 53V < battery < 51, 4.70V/4.88V
	else if((Check2 < 0x3f2)&&(Check2 >= 0x3da))		
		{
		voice_EN = 1;
		SC_Speech(10);  
		Delay(100);
		voice_EN = 0;
		}
	// 15km, 50V < battery < 51V, 4.63V/4.88V 
	else if((Check2 < 0x3d9)&&(Check2 >= 0x3cb))		
		{
		voice_EN = 1;
		SC_Speech(9);  	
		Delay(100);
		voice_EN = 0;
		}
	// 10km, 48V < battery <50V, 4.5V/4.88V
	else if((Check2 < 0x3ca)&&(Check2 >= 0x3b0))		
		{
		voice_EN = 1;
		SC_Speech(8);  	
		Delay(100);
		voice_EN = 0;
		}
	// 5km, 46V < battery < 48V, 4.38V/4.88V
	else if((Check2 < 0x3af)&&(Check2 >= 0x397))		
		{
		voice_EN =1;
		SC_Speech(7);  	
		Delay(100);
		voice_EN = 0;
		}                     
	// battery is low, battery < 46V
	else if(Check2 < 0x395)
		{
		motorBAT_low_speech();
		
		BAT_Lowflag = 1;
		}
	}

/*---------------------------------------------------
	end of file
----------------------------------------------------*/