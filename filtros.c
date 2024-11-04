
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
	    const TickType_t xFrequency = ulPeriodMs;

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

	            //printf("%6.2f, %6.2f\r\n", data, sinal_filtrado);
	        }
	        vTaskDelayUntil(&xLastWakeTime, xFrequency);
	    }
	}


void filtroiir_PassaAlta(void *pvParameters){
	uint32_t ulPeriodMs = (uint32_t)pvParameters;

	    TickType_t xLastWakeTime;
	    const TickType_t xFrequency = ulPeriodMs;

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


	            //printf("%6.2f, %6.2f\r\n", data, sinal_filtrado);
	        }
	        vTaskDelayUntil(&xLastWakeTime, xFrequency);
	    }
	}

void CriarSinalcomRuido(void *pvParameters){
	uint32_t ulPeriodMs = (uint32_t)pvParameters;

	    TickType_t xLastWakeTime;
	    const TickType_t xFrequency = ulPeriodMs;

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
