
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

