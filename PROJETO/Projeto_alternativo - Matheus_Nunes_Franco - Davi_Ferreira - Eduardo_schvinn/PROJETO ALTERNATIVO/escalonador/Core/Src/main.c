
#include "main.h"
#include "FreeRTOS.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "RM_Periodic_Scheduler.h"
#include "filtros.h"

void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);
void MX_USART1_UART_Init(void);


int main(void)
{

	HAL_Init();
	DWT->CTRL |= (1<<0);

	const int  TAMANHO_FILA = 100;

  /* USER CODE BEGIN 1 */

	dataQueue = xQueueCreate(TAMANHO_FILA, sizeof(float32_t));
	initTaskManager();
	CriaTarefaPeriodica(filtroiir_Passabaixa,"Tarefa_T1", 100, configMINIMAL_STACK_SIZE);
	//CriaTarefaPeriodica(filtroiir_PassaAlta,"Tarefa_T1", 100, configMINIMAL_STACK_SIZE);
	CriaTarefaPeriodica(CriarSinalcomRuido,"Tarefa_T2", 100, configMINIMAL_STACK_SIZE);




  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  SEGGER_SYSVIEW_Conf();
  vSetVarulMaxPRIGROUPValue();
  SEGGER_SYSVIEW_Start();

  osKernelInitialize();
  MX_FREERTOS_Init();

  /*Start scheduler*/
  Scheduler_RM_PT();

  while (1)
  {

	  }


}

int __io_putchar(int ch){
	HAL_UART_Transmit(&huart1, (uint8_t*) &ch, 1, 10);
	return ch;
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }

}


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
