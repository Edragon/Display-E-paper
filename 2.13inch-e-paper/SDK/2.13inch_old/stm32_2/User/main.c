
/*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

ErrorStatus HSEStartUpStatus;


unsigned char k=0;
unsigned int size;
unsigned char HRES,VRES_byte1,VRES_byte2;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);


void lcd_chkstatus(void);
void Ultrachip_1(void);
void Ultrachip(void);
void master_IL0373_init(void);
void Ultrachip_2(void);
void pic_display(void);
unsigned char  EPD_W21_ReadDATA(void);
void driver_delay_us(unsigned int xus)
{
	for(;xus>1;xus--);
}

void driver_delay_xms(unsigned long xms)	
{	
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
	{
        for(i=0; i<256; i++);
    }
}


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
#define NVIC_VectTab_FLASH  misc.h
*******************************************************************************/
int	main(void)
{
//	unsigned int i;
	RCC_Configuration();
	//GPIO��������
	GPIO_Configuration();

	EPD_W21_Init();

	HRES=0x80;						//128
	VRES_byte1=0x01;				//296
	VRES_byte2=0x28;
	
	k=0;
	while(1)	   
	{
		EPD_W21_Init();
		driver_delay_xms(100);

		EPD_W21_WriteCMD(0x06);         //boost soft start
		EPD_W21_WriteDATA (0x17);		//A
		EPD_W21_WriteDATA (0x17);		//B
		EPD_W21_WriteDATA (0x17);		//C       

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x9f);		//LUT from OTP��128x296

		EPD_W21_WriteCMD(0x61);			//resolution setting
		EPD_W21_WriteDATA (HRES);        	 
		EPD_W21_WriteDATA (VRES_byte1);		
		EPD_W21_WriteDATA (VRES_byte2);

		EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0x97);		//WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7

		pic_display();

		EPD_W21_WriteCMD(0x12);			//DISPLAY REFRESH 	
		driver_delay_xms(100);	        //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();
		
		EPD_W21_WriteCMD(0X02);  	//power off
		lcd_chkstatus();
		EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);


		if(k==1)	
			while(1);
		else
			k++;
		driver_delay_xms(100000);	//wait for the next image	  	
	}								//out of while(1)
}


void Ultrachip(void)
{
	unsigned int i;
	for(i=0;i<4736;i++)	     
		EPD_W21_WriteDATA(0xff);
	driver_delay_xms(2);		     
} 

void Ultrachip_1(void)
{
	unsigned int i;
	for(i=0;i<4736;i++)	 
	EPD_W21_WriteDATA(G_Ultrachip[i]);
	driver_delay_xms(2);
}

void Ultrachip_2(void)
{
	unsigned int i;
	for(i=0;i<4736;i++)	     
	EPD_W21_WriteDATA(G_Ultrachip_1[i]); 
	driver_delay_xms(2);
}

void pic_display(void)
{
	if(k==0)
	{
		EPD_W21_WriteCMD(0x10);	       //��ʼ����ڰ�ͼ��
		Ultrachip(); 
		EPD_W21_WriteCMD(0x13);		     //��ʼ������ͼ��
		Ultrachip_1();
	}
	if(k==1)
	{
		EPD_W21_WriteCMD(0x10);	       //��ʼ����ڰ�ͼ��
		Ultrachip(); 
		EPD_W21_WriteCMD(0x13);		     //��ʼ������ͼ��
		Ultrachip_2();
	}
}


void lcd_chkstatus(void)
{
	unsigned char busy;
	do
	{
		EPD_W21_WriteCMD(0x71);
		busy = isEPD_W21_BUSY;
		busy =!(busy & 0x01);        
	}
	while(busy);   
	driver_delay_xms(200);                       
}
/***********************************************************
						end file
***********************************************************/

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
 
  // ��λRCCʱ������(���ڵ���ģʽ) 
  RCC_DeInit();
 
  // ʹ���ⲿ���� 
  RCC_HSEConfig(RCC_HSE_ON);
  
  // �ȴ��ⲿ�����ȶ� 
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    // �������໷Ƶ��PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
  }
  else {
    // ʹ���ڲ����� 
    RCC_HSICmd(ENABLE);
    // �ȴ����������ȶ� 
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    // �������໷Ƶ��PLLCLK = 8MHz/2 * 16 = 64 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
  }

    // ʹ��FLASH��Ԥȡ���� 
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  //���ô�����ʱֵ,FLASH_Latency_2Ϊ������ʱ����
  FLASH_SetLatency(FLASH_Latency_2);
	
  //����ϵͳ����ʱ��
  RCC_HCLKConfig(RCC_SYSCLK_Div1); 

  //���ø����豸����ʱ�ӣ�RCC_HCLK_Div1Ϊϵͳʱ�ӳ���1
  RCC_PCLK2Config(RCC_HCLK_Div1); 

  //���õ����豸����ʱ�ӣ�RCC_HCLK_Div2Ϊϵͳʱ�ӳ���2
  RCC_PCLK1Config(RCC_HCLK_Div2);
  
  //ʹ�����໷��Ƶ
  RCC_PLLCmd(ENABLE);
  
  // �ȴ����໷��Ƶ���Ƶ���ȶ� 
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
  // ѡ�����໷ʱ��Ϊϵͳʱ��Դ 
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  // �ȴ�������� 
  while(RCC_GetSYSCLKSource() != 0x08);
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
            RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,
            ENABLE);

}

/*******************************************************************************
* ������   : GPIO_Configuration
* ����         : �������ô�������GPIO���ŵĲ���
* ����         : None
* ���         : None
* ����         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10;    //abcd OE ST LT0���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_14 |GPIO_Pin_15;    //abcd OE ST LT0���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    //abcd OE ST LT0���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{ 
  //NVIC_InitTypeDef NVIC_InitStructure;
  ;
}


#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif






