/*---------------------------------------------------
	Other.c (v1.00)
	
	其他程序
---------------------------------------------------*/

#include "main.h"
#include "port.h"

#include "Other.h"
#include "Delay.h"
#include "communication.h"

/*------- Public variable declarations --------------------------*/
extern bit position_sensor_EN;  		//位置传感器，即倒地抬起传感器总开关，1的时候，检测这两个传感器
extern bit fell_flag;						//判断主机倒下后，置1
extern bit raised_flag;					//判断主机被抬起后，置1
extern tByte sensor_trigger_count;		//传感器触发计数
extern tByte sensor_1ststage_count;	//传感器第一阶段判断低电平的计数
extern tWord sensor_3rdstage_time;			//传感器进入第三阶段的时间，
extern tByte sensor_3rdstage_effcount;		//传感器进入第三阶段后，有效触碰次数的计数
extern tByte sensor_3rdstage_count;			//传感器进入第三阶段后，低电平的计数
extern tWord sensor_3rdstage_interval;		//传感器在第三阶段中，每次有效低电平计数之间的时间间隔。在这期间的低电平不认为有效。
extern tWord sensor_2ndstage_time;		//传感器进入第二阶段后流逝时间的计数
extern tByte sensor_2ndstage_count;		//传感器进入第二阶段检测时，计算低电平的时间
extern bit stolen_alarm_flag;					// when host been touch 3 times, this flag 1 before alarm voice present, not to detect sensor for 1st voice alarm.
extern bit host_stolen_alarm1_EN;      //判断为被盗报警后的第一段语音使能
extern bit host_stolen_alarm2_EN;      //判断为被盗报警后的第二段语音使能
extern tByte host_stolen_alarm1_count;		//判断为被盗报警后的第一段语音次数
extern tByte host_stolen_alarm2_count;		//判断为被盗报警后的第二段语音次数
extern bit raised_fell_flag;					//倒地或者抬起触发后，此标志位置1
extern tByte wire_broken_count;		// 作为断线后的时间检测
extern bit battery_stolen_EN;			// 作为电池被盗的使能端
extern tByte battery_stolen_count;	// 作为电池被盗的报警次数
extern bit sensor_EN;
extern tByte enable_sensor_delay_count;		// 传感器延迟的时间
extern bit enable_sensor_delayEN;

/*-------------------------------------------------------
	magnet_CW()
	电磁铁正转，顺时针，将锁打开
--------------------------------------------------------*/
void magnet_CW(void)
	{
	send_code_to_lock();

	MagentControl_1 = 1;
	MagentControl_2 = 0;
	magnet_delay();
	MagentControl_1 = 1;
	MagentControl_2 = 1;
	motor_lock = 0;
	}

/*-------------------------------------------------------
	magnet_ACW()
	电磁铁反转，逆时针，将锁关闭
--------------------------------------------------------*/
void magnet_ACW(void)
	{
	motor_lock = 1;
	MagentControl_1 = 0;
	MagentControl_2 = 1;
	magnet_delay2();
	MagentControl_1 = 1;
	MagentControl_2 = 1;
	}
	
/*----------------------------------------------------
	disable_sensor()
	打开振动传感器和三轴传感器，
----------------------------------------------------*/
void disable_sensor(void)
	{
	// disable position sensor(vertical and horizontal) and vibration sensor
	position_sensor_EN = 0;	
	sensor_EN = 0;
	// reset all the flag in sensor
	fell_flag=0;  
	raised_flag=0;
	sensor_trigger_count = 0;
	sensor_1ststage_count = 0;
	sensor_2ndstage_count = 0;
	sensor_2ndstage_time = 0;
	sensor_3rdstage_time = 0;
	sensor_3rdstage_interval = 0;
	sensor_3rdstage_count = 0;
	sensor_3rdstage_effcount = 0;
	stolen_alarm_flag = 0;
	host_stolen_alarm1_EN = 0;
	host_stolen_alarm1_count = 0;
	host_stolen_alarm2_EN = 0;
	host_stolen_alarm2_count = 0;
	
	raised_fell_flag = 0;
	
	// reset the wire broken count
	wire_broken_count = 0;
	
	// reset battery stolen
	battery_stolen_EN = 0;
	battery_stolen_count = 0;	
	}
	
/*--------------------------------------------------------
	enable_sensor()
	打开传感器，使其偷盗
---------------------------------------------------------*/
void enable_sensor(void)
	{
	// enable position sensor(vertical and horizontal) and vibration sensor
	position_sensor_EN = 1;	
	sensor_EN = 1;
	// reset relatively sensor count
	sensor_trigger_count = 0;
	sensor_1ststage_count = 0;
	enable_sensor_delayEN = 0;
	enable_sensor_delay_count = 0;	
	}

/*---------------------------------------------------
	end of file
----------------------------------------------------*/