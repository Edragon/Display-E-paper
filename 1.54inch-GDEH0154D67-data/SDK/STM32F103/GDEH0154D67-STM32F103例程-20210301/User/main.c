#include "stm32f10x.h"
#include "epaper.h" 
#include "picture.h"
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);

/************************************************
************************************************/
/////////////////////main//////////////////////////////////////
int main(void)
{

	RCC_Configuration();
	//GPIO setting
	GPIO_Configuration();
	
while(1)
{	
//Full screen refresh
///////////////////////////////////////////��һ��   ȫˢ��ʽˢ������ͼƬ
		EPD_HW_Init(); 													//Electronic paper initialization
	 	EPD_WhiteScreen_ALL(gImage_1); 					//Refresh the picture in full screen
		EPD_DeepSleep();  											//Enter deep sleep	
    driver_delay_xms(1500);

///////////////////////////////////////////�ڶ���	  ȫˢ��ʽˢ�±���ͼƬ
		EPD_HW_Init(); 													//Electronic paper initialization	
  	EPD_SetRAMValue_BaseMap(gImage_basemap);//Partial refresh background��ע�⣺�˴�ˢ����ͼƬ�ĺ�����ȫˢͼƬ�ĺ�����һ����
		EPD_DeepSleep();  											//Enter deep sleep		
		driver_delay_xms(500);	
	
///////////////////////////////////////////������   ��ˢ���¶ȡ����ԣ�51.9��C

//ע�⣺����ͼƬˢ�µ�ʱ�����ݷ�����ֱ��ִ�� EPD_Part_Update();
//      ���ͼ��һ��ˢ�µ�ʱ����������ȫ��������ϣ�һ����ִ�� EPD_Part_Update();
	
		EPD_HW_Init(); 												 //Electronic paper initialization
																											//    y         x       ��ʾ����     ��ʾ���     ��ʾ�߶�     ��ʾģʽ		
		EPD_Dis_Part(6,56,gImage_temperature,17,32,NEG); 	//    6        56         �¶�          17           32			     ����
		EPD_Dis_Part(178,56,gImage_humidity,17,32,OFF); 	//  178        56         ʪ��          17           32		       OFF	
		
		EPD_Dis_Part(31,56,gImage_Lnum5,46,88,POS); 	 		//   31        56       ������5         46           88			     ����
		EPD_Dis_Part(80,56,gImage_Lnum1,46,88,POS);		 		//   80        56       ������1         46           88			     ����
 		EPD_Dis_Part(129,136,gImage_dot,8,8,POS); 		 		//  129       136       С����           8            8					 ����
		EPD_Dis_Part(140,88,SNum9,29,56,POS); 	 			 		//  140        88       С����9         29           56				   ����
		EPD_Dis_Part(142,56,gImage_Celsius,26,24,POS); 		//  142        56         ��C            26           24		  		 ����

		EPD_Part_Update();
		EPD_DeepSleep();  										 //Enter deep sleep			
    driver_delay_xms(1500);		
		
///////////////////////////////////////////������   ��ˢ��ʪ�ȡ����ԣ�60.2%
//���þ�ˢ��ʽ����ˢ�¶����ʾ�����ʱ�򣬴�����״̬����ֻ��ҪӲ����λ�Ϳ��ԣ��������³�ʼ����

		EPD_W21_Init();												//hard reset
																											//    y         x       ��ʾ����     ��ʾ���     ��ʾ�߶�     ��ʾģʽ				
		EPD_Dis_Part(6,56,gImage_temperature,17,32,OFF);  //    6        56         �¶�          17           32			     OFF
		EPD_Dis_Part(178,56,gImage_humidity,17,32,NEG); 	//  178        56         ʪ��          17           32		       ����

		EPD_Dis_Part(31,56,gImage_Lnum6,46,88,POS); 	 		//   31        56       ������6         46           88			     ����
		EPD_Dis_Part(80,56,gImage_Lnum0,46,88,POS);		 		//   80        56       ������0         46           88			     ����
 		EPD_Dis_Part(129,136,gImage_dot,8,8,OFF); 		 		//  129       136       С����           8            8					 ����
		EPD_Dis_Part(140,88,SNum9,29,56,OFF); 	 			 		//  140        88       С����9         29           56				   OFF
		EPD_Dis_Part(142,56,gImage_Celsius,26,24,OFF); 		//  142        56         ��C            26           24		  		 OFF
		EPD_Dis_Part(129,104,gImage_dot,8,8,POS); 		 		//  129       104       С����           8            8		  		 ����
		EPD_Dis_Part(140,56,SNum2,29,56,POS); 	 			 		//  140        56       С����2         29           56		  		 ����
  	EPD_Dis_Part(139,120,gImage_Percent,31,24,POS);		//  139       120          %            31           24		  		 ����

		EPD_Part_Update();
		EPD_DeepSleep();  									 //Enter deep sleep			
    driver_delay_xms(1500);		

///////////////////////////////////////////������   ������������ز���ȫˢ��ʽ��

		EPD_HW_Init(); 											//Electronic paper initialization
		EPD_WhiteScreen_White();  					//Show all white
		EPD_DeepSleep();  									//Enter deep sleep		
		
//////////////////////Partial screen refresh/////////////////////////////////////
///////////////////////////////////////////������   ��ˢ��ʽˢ������ͼƬ

    EPD_HW_Init(); //Electronic paper initialization	
																											//    y         x       ��ʾ����     ��ʾ���     ��ʾ�߶�     ��ʾģʽ				
	  EPD_Dis_Part(0,0,gImage_1,200,200,POS); 					//    0         0        ͼƬ1         200          200		       ����
		EPD_Part_Update();	
		EPD_DeepSleep();  //Enter deep sleep					
	  driver_delay_xms(1000);	

///////////////////////////////////////////������   ��ˢ��ʽˢ������ͼƬ

		EPD_W21_Init();											//hard reset
																											//    y         x       ��ʾ����     ��ʾ���     ��ʾ�߶�     ��ʾģʽ						
	  EPD_Dis_Part(0,0,gImage_basemap,200,200,POS); 		//    0         0       ����ͼƬ       200          200		       ����
		EPD_Part_Update();		
		EPD_DeepSleep();  									//Enter deep sleep		
    driver_delay_xms(1500);	
		
////////////////////////////////////////////////////////////////////////	
///////////////////////////////////////////�ڰ���   ����

		EPD_HW_Init(); 											//Electronic paper initialization
		EPD_WhiteScreen_White(); 						//Show all white
		EPD_DeepSleep();  									//Enter deep sleep
		while(1);		

}
//ע�⣺��Ļˢ����ϱ���������ߡ�
///////////////////////////////////////////////////////////

}






/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
 
  // Reset RCC clock configuration
  RCC_DeInit();
 
  // Enable external crystal
  RCC_HSEConfig(RCC_HSE_ON);
  
  // Waiting for the external crystal to stabilize
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    // Set the phase-locked loop frequency PLLCLK = 8MHz * 9 = 72 MHz
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
  }
  else {
    // Enable internal crystal
    RCC_HSICmd(ENABLE);
    // Waiting for the internal crystal to stabilize
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

    // Set the phase-locked loop frequency PLLCLK = 8MHz/2 * 16 = 64 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
  }

    // Enable flash prefetch cache
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  //Set the code delay, FLASH_Latency_2 is two delay cycles
  FLASH_SetLatency(FLASH_Latency_2);
	
  //Set the system total clock
  RCC_HCLKConfig(RCC_SYSCLK_Div1); 

  //Set the high speed device total clock, RCC_HCLK_Div1 is the system clock divided by 1
  RCC_PCLK2Config(RCC_HCLK_Div1); 

  //Set the low speed device total clock, RCC_HCLK_Div2 is the system clock divided by 2
  RCC_PCLK1Config(RCC_HCLK_Div2);
  
  //Enable phase-locked loop multiplier
  RCC_PLLCmd(ENABLE);
  
  // Waiting for the frequency of the phase-locked loop to multiply after frequency stabilization
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
  
  // Select the phase-locked loop clock as the system clock
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  
  // Waiting for setup to complete
  while(RCC_GetSYSCLKSource() != 0x08);
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
            RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,
            ENABLE);

}

/*******************************************************************************
* Function Name  :  GPIO_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);//ʹ��PD��E�˿�ʱ��
	  				     	
	
	 //CS-->PD8   SCK-->PD9  SDO--->PD10 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;		//Port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  	
	
	
	
	 // D/C--->PE15	   RES-->PE14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;		//Port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     		
	
	// BUSY--->PE13
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//Pull down input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				//Initialize GPIO
	
	 //LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		//Port configuration
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 		
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






