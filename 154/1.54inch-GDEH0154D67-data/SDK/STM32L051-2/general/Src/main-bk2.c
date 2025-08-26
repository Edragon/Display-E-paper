/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "EPAPER.h" 
#include "picture.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	
	//Full screen refresh
	///////////////////////////////////////////第一屏   全刷方式刷新整张图片
			EPD_HW_Init(); 													//Electronic paper initialization
			EPD_WhiteScreen_ALL(gImage_1); 					//Refresh the picture in full screen
			EPD_DeepSleep();  											//Enter deep sleep	
		driver_delay_xms(1500);

	///////////////////////////////////////////第二屏	  全刷方式刷新背景图片
			EPD_HW_Init(); 													//Electronic paper initialization	
		EPD_SetRAMValue_BaseMap(gImage_basemap);//Partial refresh background（注意：此处刷背景图片的函数和全刷图片的函数不一样）
			EPD_DeepSleep();  											//Enter deep sleep		
			driver_delay_xms(500);	
		
	///////////////////////////////////////////第三屏   局刷“温度”负显，51.9°C

	//注意：单个图片刷新的时候，数据发送完直接执行 EPD_Part_Update();
	//      多个图标一起刷新的时候，所有数据全都发送完毕，一次性执行 EPD_Part_Update();
		
			EPD_HW_Init(); 												 //Electronic paper initialization
																												//    y         x       显示内容     显示宽度     显示高度     显示模式		
			EPD_Dis_Part(6,56,gImage_temperature,17,32,NEG); 	//    6        56         温度          17           32			     负显
			EPD_Dis_Part(178,56,gImage_humidity,17,32,OFF); 	//  178        56         湿度          17           32		       OFF	
			
			EPD_Dis_Part(31,56,gImage_Lnum5,46,88,POS); 	 		//   31        56       大数字5         46           88			     正显
			EPD_Dis_Part(80,56,gImage_Lnum1,46,88,POS);		 		//   80        56       大数字1         46           88			     正显
			EPD_Dis_Part(129,136,gImage_dot,8,8,POS); 		 		//  129       136       小数点           8            8					 正显
			EPD_Dis_Part(140,88,SNum9,29,56,POS); 	 			 		//  140        88       小数字9         29           56				   正显
			EPD_Dis_Part(142,56,gImage_Celsius,26,24,POS); 		//  142        56         °C            26           24		  		 正显

			EPD_Part_Update();
			EPD_DeepSleep();  										 //Enter deep sleep			
		driver_delay_xms(1500);		
			
	///////////////////////////////////////////第四屏   局刷“湿度”负显，60.2%
	//采用局刷方式连续刷新多个显示界面的时候，从休眠状态唤醒只需要硬件复位就可以，无需重新初始化。

			EPD_W21_Init();												//hard reset
																												//    y         x       显示内容     显示宽度     显示高度     显示模式				
			EPD_Dis_Part(6,56,gImage_temperature,17,32,OFF);  //    6        56         温度          17           32			     OFF
			EPD_Dis_Part(178,56,gImage_humidity,17,32,NEG); 	//  178        56         湿度          17           32		       负显

			EPD_Dis_Part(31,56,gImage_Lnum6,46,88,POS); 	 		//   31        56       大数字6         46           88			     正显
			EPD_Dis_Part(80,56,gImage_Lnum0,46,88,POS);		 		//   80        56       大数字0         46           88			     正显
			EPD_Dis_Part(129,136,gImage_dot,8,8,OFF); 		 		//  129       136       小数点           8            8					 正显
			EPD_Dis_Part(140,88,SNum9,29,56,OFF); 	 			 		//  140        88       小数字9         29           56				   OFF
			EPD_Dis_Part(142,56,gImage_Celsius,26,24,OFF); 		//  142        56         °C            26           24		  		 OFF
			EPD_Dis_Part(129,104,gImage_dot,8,8,POS); 		 		//  129       104       小数点           8            8		  		 正显
			EPD_Dis_Part(140,56,SNum2,29,56,POS); 	 			 		//  140        56       小数字2         29           56		  		 正显
		EPD_Dis_Part(139,120,gImage_Percent,31,24,POS);		//  139       120          %            31           24		  		 正显

			EPD_Part_Update();
			EPD_DeepSleep();  									 //Enter deep sleep			
		driver_delay_xms(1500);		

	///////////////////////////////////////////第五屏   清屏（清屏务必采用全刷方式）

			EPD_HW_Init(); 											//Electronic paper initialization
			EPD_WhiteScreen_White();  					//Show all white
			EPD_DeepSleep();  									//Enter deep sleep		
			
	//////////////////////Partial screen refresh/////////////////////////////////////
	///////////////////////////////////////////第六屏   局刷方式刷新整张图片

		EPD_HW_Init(); //Electronic paper initialization	
																												//    y         x       显示内容     显示宽度     显示高度     显示模式				
		  EPD_Dis_Part(0,0,gImage_1,200,200,POS); 					//    0         0        图片1         200          200		       正显
			EPD_Part_Update();	
			EPD_DeepSleep();  //Enter deep sleep					
		  driver_delay_xms(1000);	

	///////////////////////////////////////////第七屏   局刷方式刷新整张图片

			EPD_W21_Init();											//hard reset
																												//    y         x       显示内容     显示宽度     显示高度     显示模式						
		  EPD_Dis_Part(0,0,gImage_basemap,200,200,POS); 		//    0         0       背景图片       200          200		       正显
			EPD_Part_Update();		
			EPD_DeepSleep();  									//Enter deep sleep		
		driver_delay_xms(1500);	
			
	////////////////////////////////////////////////////////////////////////	
	///////////////////////////////////////////第八屏   清屏

			EPD_HW_Init(); 											//Electronic paper initialization
			EPD_WhiteScreen_White(); 						//Show all white
			EPD_DeepSleep();  									//Enter deep sleep
			while(1);		

	
	//注意：屏幕刷新完毕必须进入休眠。
	///////////////////////////////////////////////////////////
	
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_Pin|INK_MOSI_Pin|INK_CLK_Pin|INK_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, INK_DC_Pin|INK_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin INK_MOSI_Pin INK_CLK_Pin INK_CS_Pin */
  GPIO_InitStruct.Pin = LED_Pin|INK_MOSI_Pin|INK_CLK_Pin|INK_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ST25_INT_Pin INK_BUSY_Pin */
  GPIO_InitStruct.Pin = ST25_INT_Pin|INK_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : INK_DC_Pin INK_RST_Pin */
  GPIO_InitStruct.Pin = INK_DC_Pin|INK_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF1_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
