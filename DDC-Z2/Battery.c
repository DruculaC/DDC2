/*---------------------------------------------------
	Battery.c (v1.00)
	
	电池电量判断
---------------------------------------------------*/	

#include "main.h"
#include "port.h"

#include "Battery.h"
#include "voice.h"
#include "Delay.h"

/*------ public variable -----------------------------------*/
extern tByte key_rotated_on_flag;

/*----------------------------------------------------
	verifybattery()
	voice alarm for battery status
-----------------------------------------------------*/

void verifybattery(tWord Check2)
	{	
	// battery is sufficient, battery > 55V, 3.74V/4.96V
	if((Check2 >= 0x304))
		{
		voice_EN = 1;
		SC_Speech(28);  	
		Delay(50);
		voice_EN = 0;
		}
   // 20km, 52V < battery < 55, 3.59V/4.96V
	else if((Check2 < 0x300)&&(Check2 >= 0x2e5))		
		{
		voice_EN = 1;
		SC_Speech(10);  
		Delay(80);
		voice_EN = 0;
		}
	// 15km, 50V < battery < 52V, 3.50V/4.96V 
	else if((Check2 < 0x2e0)&&(Check2 >= 0x2d2))		
		{
		voice_EN = 1;
		SC_Speech(9);  	
		Delay(80);
		voice_EN = 0;
		}
	// 10km, 48V < battery <50V, 3.4V/4.96V
	else if((Check2 < 0x2d0)&&(Check2 >= 0x2be))		
		{
		voice_EN = 1;
		SC_Speech(8);  	
		Delay(80);
		voice_EN = 0;
		}
	// 5km, 46V < battery < 48V, 3.3V/4.96V
	else if((Check2 < 0x2ba)&&(Check2 >= 0x2a9))		
		{
		voice_EN =1;
		SC_Speech(7);  	//4V电量充足提示
		Delay(80);
		voice_EN = 0;
		}                     
	// battery is low, battery < 46V
	else if(Check2 < 0x2a4)
		{
		motorBAT_low_speech();
		}
	}

/*---------------------------------------------------
	end of file
----------------------------------------------------*/