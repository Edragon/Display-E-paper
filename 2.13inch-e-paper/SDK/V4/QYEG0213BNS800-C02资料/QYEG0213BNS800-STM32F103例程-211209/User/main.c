#include "stm32f10x.h"
#include "epaper.h" 
#include "picture.h"
ErrorStatus HSEStartUpStatus;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);


/////////////////////main//////////////////////////////////////
int main(void)
{
	#ifdef DEBUG
	  debug();
	#endif
	RCC_Configuration();
	//GPIO setting
	GPIO_Configuration();


///////////////////////////////////////////��һ����	
	  //ȫ��ˢ��
		
		EPD_HW_Init(); 											//Electronic paper initialization
	 	EPD_WhiteScreen_ALL(gImage_1); 			//Refresh the picture in full screen
		EPD_DeepSleep();  									//Enter deep sleep	    ע�⣺��ˢ��ϱ���������ߣ���ʱ�䲻�������߻�Ӱ����Ļ��ʾЧ��������������		
    driver_delay_xms(3000);
/*	
		EPD_HW_Init(); 											//Electronic paper initialization
		EPD_SetRAMValue_BaseMap(gImage_2);  //Full brush background image��ע�⣺�˺�����ȫˢͼƬ����������
		EPD_DeepSleep();  									//Enter deep sleep	    ע�⣺��ˢ��ϱ���������ߣ���ʱ�䲻�������߻�Ӱ����Ļ��ʾЧ��������������
    driver_delay_xms(1000);	
	

///////////////////////////////////////////�ڶ�����	
//���ͼƬͬʱˢ�¡�ע�⣺���ͼ��һ��ˢ�µ�ʱ����������ȫ��������ϣ�һ����ִ�� EPD_Part_Update();
/////////////////   51.9%  ���2��    ////////////////////////////////////
		EPD_HW_Init(); 											//Electronic paper initialization   
																												//    y         x       ��ʾ����     ��ʾ���     ��ʾ�߶�     ��ʾģʽ
		EPD_Dis_Part(11,16,gImage_num5,46,88,ON); 					//   11			   16	       ����5          46           88           ON
		EPD_Dis_Part(61,16,gImage_num1,46,88,ON); 					//   61	       16				 ����1          46           88           ON
		EPD_Dis_Part(119,16,gImage_num9,46,88,ON); 				  //  119		     16			   ����9          46           88           ON
		EPD_Dis_Part(174,16,gImage_Percent,32,32,ON);       //  174        16  			 �ٷֺ�         32           32           ON
		EPD_Dis_Part(168,72,gImage_Celsius,38,32,OFF);      //  168			   72        ���϶�         38           32 	       OFF
 
		EPD_Dis_Part(215,16,black_block,4,8,OFF);           //  215        16      ������߸�        4            8          OFF
		EPD_Dis_Part(220,16,black_block,4,8,ON);            //  220        16			 �����ڶ���        4            8           ON
		EPD_Dis_Part(225,16,black_block,4,8,ON); 					  //  225        16      ����������        4            8           ON
		EPD_Dis_Part(230,16,black_block,4,8,ON); 					  //  230        16      ������͸�        4            8           ON
		
		EPD_Dis_Part(211,96,black_block,5,8,ON); 					  //  211        96      �ź���͸�        5            8           ON
		EPD_Dis_Part(218,88,black_block,5,16,ON);           //  218        88			 �źŵڶ���        5           16           ON
		EPD_Dis_Part(225,80,black_block,5,24,OFF); 					//  225        80			 �źŵ�����        5           24          OFF
		EPD_Dis_Part(232,72,black_block,5,32,OFF);          //  232        72			 �źŵ��ĸ�        5           32          OFF
		
		EPD_Part_Update();
		EPD_DeepSleep(); 										//Enter deep sleep	    ע�⣺��ˢ��ϱ���������ߣ���ʱ�䲻�������߻�Ӱ����Ļ��ʾЧ��������������
    driver_delay_xms(1500);

//���þ�ˢ��ʽ����ˢ�¶����ʾ�����ʱ�򣬴�����״̬����ֻ��ҪӲ����λ�Ϳ��ԣ��������³�ʼ����		
/////////////////   30.2���϶�  �ź�3��    ////////////////////////////////////
		EPD_W21_Init();											//hard reset																			
																												//    y         x       ��ʾ����     ��ʾ���     ��ʾ�߶�     ��ʾģʽ		
		EPD_Dis_Part(11,16,gImage_num3,46,88,ON); 					//   11			   16	       ����3          46           88           ON
		EPD_Dis_Part(61,16,gImage_num0,46,88,ON); 					//   61	       16				 ����0          46           88           ON
		EPD_Dis_Part(119,16,gImage_num2,46,88,ON); 					//  119		     16			   ����2          46           88           ON
    EPD_Dis_Part(174,16,gImage_Percent,32,32,OFF); 			//  174        16  			 �ٷֺ�         32           32          OFF
		EPD_Dis_Part(168,72,gImage_Celsius,38,32,ON); 			//  168			   72        ���϶�         38           32 	        ON
		
		EPD_Dis_Part(215,16,black_block,4,8,OFF);           //  215        16      ������߸�        4            8          OFF
		EPD_Dis_Part(220,16,black_block,4,8,OFF);           //  220        16			 �����ڶ���        4            8          OFF
		EPD_Dis_Part(225,16,black_block,4,8,ON); 						//  225        16      ����������        4            8           ON
		EPD_Dis_Part(230,16,black_block,4,8,ON); 						//  230        16      ������͸�        4            8           ON
				
		EPD_Dis_Part(211,96,black_block,5,8,ON); 						//  211        96      �ź���͸�        5            8           ON
		EPD_Dis_Part(218,88,black_block,5,16,ON); 					//  218        88			 �źŵڶ���        5           16           ON
		EPD_Dis_Part(225,80,black_block,5,24,ON); 					//  225        80			 �źŵ�����        5           24           ON
		EPD_Dis_Part(232,72,black_block,5,32,OFF); 					//  232        72			 �źŵ��ĸ�        5           32          OFF

		EPD_Part_Update();
		EPD_DeepSleep();  									//Enter deep sleep	    ע�⣺��ˢ��ϱ���������ߣ���ʱ�䲻�������߻�Ӱ����Ļ��ʾЧ��������������
    driver_delay_xms(1500);

///////////////////////////////////////////��������	
//////////////////////Partial screen refresh/////////////////////////////////////
//ע�⣺�Ӿ�ˢ��ʽת��ȫˢ��ʽ��ʱ�����ߺ�һ��Ҫ���³�ʼ��

		EPD_HW_Init(); 											//Electronic paper initialization
		EPD_WhiteScreen_White();  					//Show all white
																												//    y         x       ��ʾ����     ��ʾ���     ��ʾ�߶�     ��ʾģʽ				
		EPD_HW_Init(); 											//Electronic paper initialization
	  EPD_Dis_Part(0,0,gImage_1,250,128,ON); 							//    0         0       gImage_1        250         128           ON
		EPD_Part_Update();
		EPD_DeepSleep();  									//Enter deep sleep				
	  driver_delay_xms(1000);	

		EPD_W21_Init(); 										//hard reset	
		EPD_Dis_Part(0,0,gImage_2,250,128,ON);              //    0         0       gImage_2        250         128           ON
		EPD_Part_Update();
		EPD_DeepSleep();  									//Enter deep sleep					
    driver_delay_xms(1000);		
*/		
			
////////////////////////////////////////////////////////////////////////	
		//Clear screen
		EPD_HW_Init(); 											//Electronic paper initialization
		EPD_WhiteScreen_White();  					//Show all white
		EPD_DeepSleep();  									//Enter deep sleep	
		while(1);		

}
///////////////////////////////////////////////////////////





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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //Floating input
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);    //Initialize GPIO
	
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






