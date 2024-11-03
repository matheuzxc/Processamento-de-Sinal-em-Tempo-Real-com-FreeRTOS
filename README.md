# Processamento-de-Sinal-em-Tempo-Real-com-FreeRTOS

Este projeto implementa um sistema de processamento de sinal em tempo real usando o FreeRTOS, focado na aplicação de filtros IIR (Infinite Impulse Response) e no gerenciamento de tarefas periódicas em um microcontrolador STM32. A integração do MATLAB permite o design e a análise prévia dos filtros IIR, com uma transição fluida para a implementação em um ambiente embarcado.

## Índice

- [Descrição do Projeto](#descrição-do-projeto)
- [Estrutura do Sistema](#estrutura-do-sistema)
- [Hardware Utilizado](#hardware-utilizado)
- [Instalação](#instalação)
- [Execução](#execução)
- [Resultados](#resultados)
- [Considerações Finais](#considerações-finais)
- [Autores](#autores)
- [Licença](#licença)

## Descrição do Projeto

O objetivo deste projeto é implementar um sistema de filtragem digital em tempo real utilizando filtros IIR, com o FreeRTOS para gerenciar tarefas periódicas. O projeto utiliza o MATLAB para projetar os filtros, possibilitando a filtragem de sinais que simulam vibrações mecânicas e ruídos típicos de sistemas industriais.

## Estrutura do Sistema

- **Geração de Sinal com Ruído**: Criação de uma onda senoidal de 5 Hz com ruído adicionado para simular condições reais de vibração.
- **Filtros IIR**: Filtros Chebyshev passa-baixa e passa-alta, projetados no MATLAB e aplicados no STM32 para atenuação do ruído.
- **Tarefas Periódicas com FreeRTOS**: Gerenciamento eficiente de tarefas de geração e filtragem de sinal, com sincronização de dados via filas e proteção por mutex.
- **Escalonamento Rate-Monotonic (RM)**: Uso do algoritmo RM para priorizar tarefas com base nos períodos e garantir que todas sejam executadas dentro dos prazos.

## Hardware Utilizado

- **Microcontrolador**: STM32F103C8T6 (Blue Pill)
- **Conversor USB-UART**: FTDI232 para comunicação com o PC
- **Ferramenta de Monitoramento**: SystemView, para rastreamento em tempo real das tarefas no microcontrolador.

## Instalação

1. **Pré-requisitos**:
   - STM32CubeIDE: Ambiente de desenvolvimento integrado para STM32.
   - MATLAB: Para projeto e análise dos filtros IIR.
   - SystemView (SEGGER): Para análise de execução em tempo real.

2. **Configuração do Ambiente**:
   - Configure o STM32CubeIDE para o microcontrolador STM32F103C8T6.
   - Instale as bibliotecas do FreeRTOS no STM32CubeIDE.

3. **Clonando o Repositório**:
   ```bash
   git clone https://github.com/seu_usuario/nome_do_projeto.git
   cd nome_do_projeto

