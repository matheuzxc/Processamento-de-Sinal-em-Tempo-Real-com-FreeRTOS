
#ifndef RM_PERIODIC_SCHEDULER_H
#define RM_PERIODIC_SCHEDULER_H

#include "cmsis_os.h"
#include "gpio.h"
#include "stdio.h"
#include "semphr.h"
#include "task.h"
#include "memory.h"
#include "stdlib.h"
#include "queue.h"


typedef struct {
    TaskHandle_t *vet_tasks;
    int qtd_tarefas;
    int *periodos;
    int size;
} TaskManager_t;




void initTaskManager();
void CriaTarefaPeriodica(TaskFunction_t pvTaskCode,const char *pcName, uint32_t ulPeriodMs, uint32_t ulStackDepth);
void Scheduler_RM_PT ();

#endif
