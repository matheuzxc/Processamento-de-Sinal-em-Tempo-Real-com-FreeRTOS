#ifndef FILTROS_H
#define FILTROS_H
//alterar
#define PI 3.14159265358979


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#define ARM_MATH_CM3
#include "arm_math.h"
#include "math.h"

extern float32_t x,x_1,x_2,y_1,y_2;
extern float32_t y;
extern float32_t yr;
extern float32_t entrada;
extern QueueHandle_t dataQueue;



void filtroiir_Passabaixa();
void filtroiir_PassaAlta();
void CriarSinalcomRuido();
#endif
