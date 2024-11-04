################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/SEGGER/Config/%.o Middlewares/Third_Party/SEGGER/Config/%.su Middlewares/Third_Party/SEGGER/Config/%.cyclo: ../Middlewares/Third_Party/SEGGER/Config/%.c Middlewares/Third_Party/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"/home/matheus/Projeto_alternativo - Matheus_Nunes_Franco - Davi_Ferreira - Eduardo_schvinn/PROJETO ALTERNATIVO/escalonador/Middlewares/Third_Party/SEGGER/Config" -I"/home/matheus/Projeto_alternativo - Matheus_Nunes_Franco - Davi_Ferreira - Eduardo_schvinn/PROJETO ALTERNATIVO/escalonador/Middlewares/Third_Party/SEGGER/OS" -I"/home/matheus/Projeto_alternativo - Matheus_Nunes_Franco - Davi_Ferreira - Eduardo_schvinn/PROJETO ALTERNATIVO/escalonador/Middlewares/Third_Party/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Config

clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Config:
	-$(RM) ./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o ./Middlewares/Third_Party/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-SEGGER-2f-Config

