/*---------------------------------------------------
	Other.c (v1.00)
	
	��������
---------------------------------------------------*/

#include "main.h"
#include "port.h"

#include "Other.h"
#include "Delay.h"
#include "communication.h"

/*------- Public variable declarations --------------------------*/
extern bit position_sensor_EN;  		//λ�ô�������������̧�𴫸����ܿ��أ�1��ʱ�򣬼��������������
extern bit fell_flag;						//�ж��������º���1
extern bit raised_flag;					//�ж�������̧�����1
extern tByte sensor_trigger_count;		//��������������
extern tByte sensor_1ststage_count;	//��������һ�׶��жϵ͵�ƽ�ļ���
extern tWord sensor_3rdstage_time;			//��������������׶ε�ʱ�䣬
extern tByte sensor_3rdstage_effcount;		//��������������׶κ���Ч���������ļ���
extern tByte sensor_3rdstage_count;			//��������������׶κ󣬵͵�ƽ�ļ���
extern tWord sensor_3rdstage_interval;		//�������ڵ����׶��У�ÿ����Ч�͵�ƽ����֮���ʱ�����������ڼ�ĵ͵�ƽ����Ϊ��Ч��
extern tWord sensor_2ndstage_time;		//����������ڶ��׶κ�����ʱ��ļ���
extern tByte sensor_2ndstage_count;		//����������ڶ��׶μ��ʱ������͵�ƽ��ʱ��
extern bit stolen_alarm_flag;					// when host been touch 3 times, this flag 1 before alarm voice present, not to detect sensor for 1st voice alarm.
extern bit host_stolen_alarm1_EN;      //�ж�Ϊ����������ĵ�һ������ʹ��
extern bit host_stolen_alarm2_EN;      //�ж�Ϊ����������ĵڶ�������ʹ��
extern tByte host_stolen_alarm1_count;		//�ж�Ϊ����������ĵ�һ����������
extern tByte host_stolen_alarm2_count;		//�ж�Ϊ����������ĵڶ�����������
extern bit raised_fell_flag;					//���ػ���̧�𴥷��󣬴˱�־λ��1
extern tByte wire_broken_count;		// ��Ϊ���ߺ��ʱ����
extern bit battery_stolen_EN;			// ��Ϊ��ر�����ʹ�ܶ�
extern tByte battery_stolen_count;	// ��Ϊ��ر����ı�������
extern bit sensor_EN;
extern tByte enable_sensor_delay_count;		// �������ӳٵ�ʱ��
extern bit enable_sensor_delayEN;

/*-------------------------------------------------------
	magnet_CW()
	�������ת��˳ʱ�룬������
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
	�������ת����ʱ�룬�����ر�
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
	���񶯴����������ᴫ������
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
	�򿪴�������ʹ��͵��
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