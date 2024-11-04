
 
``` bash 
Alunos: Davi Ferreira, Eduardo Schvinn e Matheus Nunes Franco
Professor: Gian Ricardo Berkenbrock
Curso: EMB5633
```
# Desenvolvimento de Sistema de Processamento de Sinal em Tempo Real com FreeRTOS: Aplicaçoes em Filtro IIR e Tarefas Periódicas.

Este projeto propoe a implementaçao de um sistema de processamento de sinal em tempo
real com base no FreeRTOS, um sistema operacional de
tempo real de código aberto. O foco central do sistema e a
aplicaçao de filtros de Resposta ao Impulso Infinito (IIR) e
tarefas periodicas.

# 📦Pré-Requistos 📦

##  IDEcube

[Guia de Instalação](https://www.st.com/content/st_com/en/stm32cubeide.html?dl=nKzTTu31%2BI9uYlKZKAs6Sw%3D%3D%2CTDyj5BbmTnin7IWxAiVtLT2wLdloB5g0vm0MsS2%2B59O6yFQP9BOPAZXtabmDtmNG4GAP%2FiFGQ2WYKW6uY88ed6jFYM7Kh%2FLqjHpQ5%2FHHgvNJFr9wCUx5KMEbbkUZXTc53BCDBXzhGXWPCiReZAycwiv4XtSsr4QPE9Eh53a5iqem3xXJbEfnk68nUQbUOMQzq93DDgLceXtGOSZ5CFvD%2B5DWvTQr5FXNFPRQ1FEYZvp69dPp9M9m1Qop8EW9kZ2%2Fiuohl4J%2F7pJOncctEdTyjURGcvg7bxtNSmibkcFVdrn4OeExR4O%2F%2FxkjapKLay8Wd%2FF%2BLcjKVXvnU068M5q9RJfHzuBuMT9kMYgVgJcSwxcEpw8TnPUtRAYCMMtXFQeT7LpR59A4IjCBv0H0%2FuY4PwQcnbAUn3b2k%2B30HLT%2F8m0AXomSHvuD9EnvVSkQDZo3DQzQqWfsWXVtVF7UBRgxVw%3D%3D)


## systemview
   [Guia de Instalação](https://www.segger.com/downloads/systemview/)


# Funcionamento IDEcube

<li>abra o IDEcube</li>
<li>vá em file </li>
<li>clique em open project</li>
<li>clique no botão directory e abra o projeto</li>
<h1> </h1>

# Como colocar código no IDECUBE

## Foi desenvolvida um escalonador para o FreeRTOS, chamado de "RM_Periodic_Scheduler".
### Estes códigos podem ser encontrados na pasta "projeto alternativo/CÓDIGOS_STM32"
```


#include "RM_Periodic_Scheduler.h"
#include "filtros.h"

TaskManager_t taskManager;

void initTaskManager (){
	taskManager.vet_tasks = NULL;
	taskManager.qtd_tarefas= 0;
	taskManager.periodos = NULL;
	taskManager.size = 0;
}

void CriaTarefaPeriodica(TaskFunction_t pvTaskCode, const char *pcName, uint32_t ulPeriodMs, uint32_t ulStackDepth) {
	TaskHandle_t xHandle = NULL;
    ulPeriodMs = pdMS_TO_TICKS(1000 / ulPeriodMs);
	//ulPeriodMs = pdMS_TO_TICKS(ulPeriodMs);
    UBaseType_t uxPriority = tskIDLE_PRIORITY;
    xTaskCreate(pvTaskCode, pcName, ulStackDepth, (void *)ulPeriodMs, uxPriority, &xHandle);

    if (taskManager.vet_tasks == NULL) {
        taskManager.vet_tasks = (TaskHandle_t *)malloc(sizeof(TaskHandle_t));
        taskManager.periodos = (int *)malloc(sizeof(int));
    } else {
        taskManager.vet_tasks = (TaskHandle_t *)realloc(taskManager.vet_tasks, (taskManager.size + 1) * sizeof(TaskHandle_t));
        taskManager.periodos = (int *)realloc(taskManager.periodos, (taskManager.size + 1) * sizeof(int));
    }

    taskManager.vet_tasks[taskManager.size] = xHandle;
    taskManager.periodos[taskManager.size] = ulPeriodMs;
    taskManager.size++;
}

void Scheduler_RM_PT() {
    if (taskManager.vet_tasks == NULL) {
        return;
    }

    int trocou;
    for (int passo = 0; passo < taskManager.size - 1; passo++) {
        trocou = 0;
        for (int i = 0; i < taskManager.size - passo - 1; i++) {
            if (taskManager.periodos[i] > taskManager.periodos[i + 1]) {
                // Trocar elementos
                int aux = taskManager.periodos[i];
                taskManager.periodos[i] = taskManager.periodos[i + 1];
                taskManager.periodos[i + 1] = aux;

                TaskHandle_t aux_task = taskManager.vet_tasks[i];
                taskManager.vet_tasks[i] = taskManager.vet_tasks[i + 1];
                taskManager.vet_tasks[i + 1] = aux_task;

                trocou = 1;
            }
        }

        // Se nenhum elemento foi trocado, a lista está ordenada
        if (!trocou) {
            break;
        }
    }


    for (int i = 0; i < taskManager.size; i++) {
        vTaskPrioritySet(taskManager.vet_tasks[i], taskManager.size - i+1);
    }

    vTaskStartScheduler();
}



```

## Foi desenvolvida um arquivo para implementar os filtros IIR, esta e chamada de "filtros".

### Estes códigos podem ser encontrados na pasta "projeto alternativo/CÓDIGOS_STM32"

<li>O código contem duas tarefas para execução de um filtro passa baixa e passa alta.</li>
<li>A escolha do tipo de filtro deve ser feita no momento da chamada da tarefa.  </li>
<li>A função CriarSinalcomRuido, simula um sinal de 5Hz com um ruido aplicado aleatoriamente dentro um intervalo especificado e esta onda e amostrada na faixa de 100Hz</li>

```

#include "filtros.h"



float32_t x,x_1,x_2,y_1,y_2;
float32_t y;
float32_t yr = 0.0;
float32_t entrada;
QueueHandle_t dataQueue;
const int FREQUENCY = 5;

void filtroiir_Passabaixa(void *pvParameters){
	uint32_t ulPeriodMs = (uint32_t)pvParameters;

	    TickType_t xLastWakeTime;
	    const TickType_t xFrequency = pdMS_TO_TICKS(ulPeriodMs);

    xLastWakeTime = xTaskGetTickCount();

	while (1) {
	        float32_t data;
	        // Aguarde receber dados da fila
	        if (xQueueReceive(dataQueue, &data, portMAX_DELAY)) {
	            // Aplica o filtro IIR
	            float32_t x = data; // Atualize o valor de x antes de usar
	            float32_t yr = 1.699 * y_1 - 0.7601 * y_2 + 0.01356 * x + 0.02712 * x_1 + 0.01356 * x_2;



	            // Atualize os valores passados
	            x_2 = x_1;
	            x_1 = x;
	            y_2 = y_1;
	            y_1 = yr;

	            // Atualize a saída
	            float32_t sinal_filtrado = yr;

	            printf("%6.2f, %6.2f\r\n", data, sinal_filtrado);
	        }
	        vTaskDelayUntil(&xLastWakeTime, xFrequency);
	    }
	}


void filtroiir_PassaAlta(void *pvParameters){
	uint32_t ulPeriodMs = (uint32_t)pvParameters;

	    TickType_t xLastWakeTime;
	    const TickType_t xFrequency = pdMS_TO_TICKS(ulPeriodMs);

    xLastWakeTime = xTaskGetTickCount();

	while (1) {
	        float32_t data;
	        // Aguarde receber dados da fila
	        if (xQueueReceive(dataQueue, &data, portMAX_DELAY)) {
	            // Aplica o filtro IIR
	            float32_t x = data; // Atualize o valor de x antes de usar
	            float32_t yr = 1.845 * y_1 - 0.966 * y_2 + 0.2912 * x - 0.5824 * x_1 + 0.2912 * x_2;


	            // Atualize os valores passados
	            x_2 = x_1;
	            x_1 = x;
	            y_2 = y_1;
	            y_1 = yr;

	            // Atualize a saída
	            float32_t sinal_filtrado = yr;

	            // Debug: imprimir valores para verificar
	            printf("%6.2f, %6.2f\r\n", data, sinal_filtrado);
	        }
	        vTaskDelayUntil(&xLastWakeTime, xFrequency);
	    }
	}

void CriarSinalcomRuido(void *pvParameters){
	uint32_t ulPeriodMs = (uint32_t)pvParameters;

	    TickType_t xLastWakeTime;
	    const TickType_t xFrequency = pdMS_TO_TICKS(ulPeriodMs);

	    xLastWakeTime = xTaskGetTickCount();

	    while (1) {
	    	static uint32_t sample_count = 0;

	        float32_t noise = ((float32_t)rand() / RAND_MAX) * 1.2 - 0.1;

	        float32_t sin_value = arm_sin_f32(2 * PI * FREQUENCY * sample_count /100);

	        entrada = sin_value + noise;

	        xQueueSend(dataQueue, &entrada, portMAX_DELAY);

	        sample_count++;

	        vTaskDelayUntil(&xLastWakeTime, xFrequency);
	    }
}

```
### O codigo seguinte e o código do projeto, para execulta-lo, siga para o proximo passo.


```
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



```
# Execução
O projeto neste trabalho foi desenvolvido na IDE do stm32 (IDECUBE), para inicia-lo, execulte o projeto na pasta "escalonador/escalonador.ioc".

# exportação debug -> systemView
<li>no IDEcube clique em run e depois debug</li>
<li>clique f8 para iniciar o debug automatico  </li>
<li>suspenda o debug, mas nao termine somente pause</li>
<li>nas opções de ferramentas de debug clique em expressions </li>
<li>verifique a variavel _SEGGER_RTT, caso não haja, crie</li>
<li>dentro da variavél  _SEGGER_RTT vá para aUP e depois aUP{1}</li>
<li>essas variaves são responsaveis por guardar a memoria do buffer </li>
<li>dentro dela deve ser verificado e copiado o endereço da variavel pbuffer </li>
<li>e armazene também o valor de WrOff </li>
<li>após essas operações, vá na opção window </li>
<li>siga para show view e depois memory browser</li>
<li>coloque o endereço do buffer na barra de pesquisa </li>
<li>e clique em export</li>
<li> após isso inicializará uma tela para exportar a memoria</li>
<li> aplique o formato RAW binary </li>
<li> e coloque o valor de WrOff em length </li>
<li> verifique se na barra de file name o tipo de arquivo é SV.dat, caso não, aplique esse formato </li>
<li> após isso vá ao diretorio em que o arquivo foi salvo e inicialize o arquivo  </li>
<li> aproveite sua visão </li>


# Código do MATLAB
### Estes códigos podem ser encontrados na pasta "projeto alternativo/CÓDIGOS_MATLAB"

Os códigos a seguir devem ser abertos no MATLAB online.

Vá em adicionar Script e adicione o seguinte trecho de código:

```
function [onda_1,onda,T] = onda_senoidal(Fs, duracao, frequencia, amplitude, noise_amplitude)
    T = 1/Fs;
    t = 0:T:duracao-T;
    onda = amplitude * sin(2*pi*frequencia*t);
    onda_1 = onda;
    if nargin == 5
        % Adição de ruído ao sinal
        onda = onda + noise_amplitude * randn(size(t));
    end
end
```

Código que executa o filtro passa baixas.

```
Fs = 100;           % Taxa de amostragem
duracao = 10;        % Duração da onda em segundos
frequencia = 5;     % Frequência da onda senoidal em Hz
amplitude = 1;      % Amplitude da onda senoidal
noise_amplitude = 1.2;  % Amplitude do ruído

% Geração da onda senoidal
[onda_1, onda] = onda_senoidal(Fs, duracao, frequencia, amplitude, noise_amplitude);
[fx, s_f] = fourier(onda, Fs);

% Visualização da onda senoidal
figure(1);

subplot(2,1,1), plot(0:1/Fs:duracao-1/Fs, onda);
title('Onda Senoidal Gerada');
xlabel('Tempo (s)');
ylabel('Amplitude');

subplot(2,1,2), plot(fx, s_f);
grid on;
title('Transformada de Fourier da Onda Senoidal');
xlabel('Frequência (Hz)');
ylabel('Amplitude');

% Filtro Chebyshev Tipo I
figure(2);
n = 3;
wp = 6;
wn = 5/(Fs/2);
[num, den] = cheby1(n, wp, wn, 'low');
sys = tf(num, den, 1/Fs);
sfiltrada = filter(num, den, onda);

% Visualização do sinal filtrado
subplot(2,1,1), plot(0:1/Fs:duracao-1/Fs, sfiltrada);
title('Sinal Filtrado');
grid on;
xlabel('Tempo (s)');
ylabel('Amplitude');

[fsfiltrada, s_filtrada] = fourier(sfiltrada, Fs);
subplot(2,1,2), plot(fsfiltrada, s_filtrada);
title('Transformada de Fourier do Sinal Filtrado');
grid on;
xlabel('Frequência (Hz)');
ylabel('Amplitude');
```
Código que executa o filtro passa altas
```
Fs = 100;           % Taxa de amostragem
duracao = 10;        % Duração da onda em segundos
frequencia = 5;     % Frequência da onda senoidal em Hz
amplitude = 1;      % Amplitude da onda senoidal
noise_amplitude = 1.2;  % Amplitude do ruído

% Geração da onda senoidal
[onda_1, onda] = onda_senoidal(Fs, duracao, frequencia, amplitude, noise_amplitude);
[fx, s_f] = fourier(onda, Fs);

% Visualização da onda senoidal
figure(1);

subplot(2,1,1), plot(0:1/Fs:duracao-1/Fs, onda);
title('Onda Senoidal Gerada');
xlabel('Tempo (s)');
ylabel('Amplitude');

subplot(2,1,2), plot(fx, s_f);
grid on;
title('Transformada de Fourier da Onda Senoidal');
xlabel('Frequência (Hz)');
ylabel('Amplitude');

% Filtro Chebyshev Tipo I
figure(2);
n = 3;
wp = 6;
wn = 30/(Fs/2);
[num, den] = cheby1(n, wp, wn, 'low');
sys = tf(num, den, 1/Fs);
sfiltrada = filter(num, den, onda);

% Visualização do sinal filtrado
subplot(2,1,1), plot(0:1/Fs:duracao-1/Fs, sfiltrada);
title('Sinal Filtrado');
grid on;
xlabel('Tempo (s)');
ylabel('Amplitude');

[fsfiltrada, s_filtrada] = fourier(sfiltrada, Fs);
subplot(2,1,2), plot(fsfiltrada, s_filtrada);
title('Transformada de Fourier do Sinal Filtrado');
grid on;
xlabel('Frequência (Hz)');
ylabel('Amplitude');
```


### O relatório IEEE pode ser encontrado na pasta "projeto alternativo/RELATÓRIO_IEEE"

### Os dados coletados no TRACE podem ser encontrados na pasta "projeto alternativo/DADOS_COLETADOS"

<img src = "./TRACE_VIEW.png">



