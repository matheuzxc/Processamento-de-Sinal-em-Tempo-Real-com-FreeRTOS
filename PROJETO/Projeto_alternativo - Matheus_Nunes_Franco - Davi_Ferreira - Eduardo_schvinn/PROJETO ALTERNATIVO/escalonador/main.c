#include "FreeRTOS.h"
#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "stdio.h"
#include "semphr.h"
#include "task.h"
#include "RM_Periodic_Scheduler.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);

int main(void)
{

DWT->CTRL |= (1<<0);



  /* MCU Configuration--------------------------------------------------------*/
Construtor();
CriaTarefaPeriodica("Tarefa2", 2, configMINIMAL_STACK_SIZE);
CriaTarefaPeriodica("Tarefa3", 1, configMINIMAL_STACK_SIZE);

/*
CriaServidor("serv", 20, configMINIMAL_STACK_SIZE);
CriaAPE();
*/
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  SEGGER_SYSVIEW_Conf();
  vSetVarulMaxPRIGROUPValue();
  SEGGER_SYSVIEW_Start();

  osKernelInitialize();
  MX_FREERTOS_Init();

  /* Start scheduler */

  Scheduler_RM_PT();

  while (1)
  {
    /* USER CODE END WHILE */



    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
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
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
