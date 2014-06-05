#include "main.h"
#include "port.h"

#include "uart.h"


/*
函数名： void InitUART()
功能： 	初始化UART
说明：
入口参数：无
返回值：  无
*/
void InitUART()
{
	AUXR1 &=0xbf ; 
	SCON=0x5a;
	TMOD=0x20;
	TH1=TL1=-(OSC_FREQ/12/32/BAUD);
	TR1=1;
}
/*
函数名： void SendData(BYTE dat)
功能： 	发送函数
说明：
入口参数：要发送的字节
返回值：  无
*/

void SendData(unsigned char dat)
{
	SBUF=dat;
	while(!TI);TI=0;	
}

/*
函数名：void SendNByte(BYTE *buf,BYTE len)
功能： 发送多个字节
说明：
入口参数：要发送的数据地址，发送的字节长度
返回值： 无
*/
void SendNByte(unsigned char *buf, unsigned char len)
{
	while(len--)
	{
		SendData(*buf++);
	}
}


//
///*
//函数名：BYTE GetData()
//功能： 	接收函数
//说明：
//入口参数 ：无
//返回值： 接收到的数据
//*/
//unsigned char GetData(void)
//{
//	unsigned char datt;
//	while(!RI);RI=0;
//	datt=SBUF;
//	return datt;
//}




///*
//函数名：WORD  GainSum(BYTE *oneData,BYTE dataLen)
//功能：	求和函数，作为奇偶校验
//说明：
//入口参数：接收的数据部分	,数据长度
//返回值：  校验数据
//*/
//unsigned int  GainSum(unsigned char *oneData,unsigned char dataLen)
//{
//	unsigned char i=0;
//	unsigned int between=0;
//
//
//	for(i=0;i<dataLen;i++)
//	{
//	between=*oneData+between;
//	oneData+=1;
//	}
//
//	return between;
//}












