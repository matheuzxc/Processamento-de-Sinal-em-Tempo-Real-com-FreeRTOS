################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/org/Source/croutine.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/list.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/queue.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/stream_buffer.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/tasks.c \
../Middlewares/Third_Party/FreeRTOS/org/Source/timers.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/list.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/queue.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/stream_buffer.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.o \
./Middlewares/Third_Party/FreeRTOS/org/Source/timers.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/list.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/queue.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/stream_buffer.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.d \
./Middlewares/Third_Party/FreeRTOS/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/org/Source/%.o Middlewares/Third_Party/FreeRTOS/org/Source/%.su Middlewares/Third_Party/FreeRTOS/org/Source/%.cyclo: ../Middlewares/Third_Party/FreeRTOS/org/Source/%.c Middlewares/Third_Party/FreeRTOS/org/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"/home/matheus/Projeto_alternativo - Matheus_Nunes_Franco - Davi_Ferreira - Eduardo_schvinn/PROJETO ALTERNATIVO/escalonador/Middlewares/Third_Party/SEGGER/Config" -I"/home/matheus/Projeto_alternativo - Matheus_Nunes_Franco - Davi_Ferreira - Eduardo_schvinn/PROJETO ALTERNATIVO/escalonador/Middlewares/Third_Party/SEGGER/OS" -I"/home/matheus/Projeto_alternativo - Matheus_Nunes_Franco - Davi_Ferreira - Eduardo_schvinn/PROJETO ALTERNATIVO/escalonador/Middlewares/Third_Party/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.d ./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.o ./Middlewares/Third_Party/FreeRTOS/org/Source/croutine.su ./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.d ./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.o ./Middlewares/Third_Party/FreeRTOS/org/Source/event_groups.su ./Middlewares/Third_Party/FreeRTOS/org/Source/list.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/list.d ./Middlewares/Third_Party/FreeRTOS/org/Source/list.o ./Middlewares/Third_Party/FreeRTOS/org/Source/list.su ./Middlewares/Third_Party/FreeRTOS/org/Source/queue.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/queue.d ./Middlewares/Third_Party/FreeRTOS/org/Source/queue.o ./Middlewares/Third_Party/FreeRTOS/org/Source/queue.su ./Middlewares/Third_Party/FreeRTOS/org/Source/stream_buffer.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/stream_buffer.d ./Middlewares/Third_Party/FreeRTOS/org/Source/stream_buffer.o ./Middlewares/Third_Party/FreeRTOS/org/Source/stream_buffer.su ./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.d ./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.o ./Middlewares/Third_Party/FreeRTOS/org/Source/tasks.su ./Middlewares/Third_Party/FreeRTOS/org/Source/timers.cyclo ./Middlewares/Third_Party/FreeRTOS/org/Source/timers.d ./Middlewares/Third_Party/FreeRTOS/org/Source/timers.o ./Middlewares/Third_Party/FreeRTOS/org/Source/timers.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-org-2f-Source

