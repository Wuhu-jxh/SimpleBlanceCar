#include <cstdarg>
#include <cstring>
#include "SerialIO.h"
#include "main.h"
#include <cstdio>
#include "settings.h"
#include "usart.h"
extern char rxBuffer;
extern char RxBuffer[RXBUFFERSIZE];
extern int Uart1_Rx_Cnt;
//
// Created by 神奇bug在哪里 on 2023/5/4.
//
void sysLog(enum LOG_level lv, const char *str)
{
    if(lv < SERIAL_LOG_LEVEL)
        return;
    switch (lv)
    {
        case LOG_DEBUG:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[DEBUG]", sizeof "[DEBUG]", 0xFFFF);
            break;
        case LOG_INFO:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[INFO]", sizeof "[INFO]", 0xFFFF);
            break;
        case LOG_WARNING:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[WARNING]", sizeof "[WARNING]", 0xFFFF);
            break;
        case LOG_ERROR:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[ERROR]", sizeof "[ERROR]", 0xFFFF);
            break;
        case LOG_FATAL:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[FATAL]", sizeof "[FATAL]", 0xFFFF);
            break;
        default:
            break;
    }
    HAL_UART_Transmit(&huart1, (uint8_t *) str, strlen(str), 0xFFFF);
}
//void sysLog(enum LOG_level lv,std::string dat)
//{
//    if(lv < SERIAL_LOG_LEVEL)
//        return;
//    switch (lv)
//    {
//        case LOG_DEBUG:
//            HAL_UART_Transmit(&huart1, (uint8_t *) "[DEBUG]", sizeof "[DEBUG]", 0xFFFF);
//            break;
//        case LOG_INFO:
//            HAL_UART_Transmit(&huart1, (uint8_t *) "[INFO]", sizeof "[INFO]", 0xFFFF);
//            break;
//        case LOG_WARNING:
//            HAL_UART_Transmit(&huart1, (uint8_t *) "[WARNING]", sizeof "[WARNING]", 0xFFFF);
//            break;
//        case LOG_ERROR:
//            HAL_UART_Transmit(&huart1, (uint8_t *) "[ERROR]", sizeof "[ERROR]", 0xFFFF);
//            break;
//        case LOG_FATAL:
//            HAL_UART_Transmit(&huart1, (uint8_t *) "[FATAL]", sizeof "[FATAL]", 0xFFFF);
//            break;
//        default:
//            break;
//    }
//    HAL_UART_Transmit(&huart1, (uint8_t *) dat.c_str(), dat.length(), 0xFFFF);
//}
void sysLogf(enum LOG_level lv,char *format,...)
{
    if(lv < SERIAL_LOG_LEVEL)
        return;
    va_list args;
    va_start(args,format);
    switch (lv)
    {
        case LOG_DEBUG:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[DEBUG]", sizeof "[DEBUG]", 0xFFFF);
        case LOG_INFO:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[INFO]", sizeof "[INFO]", 0xFFFF);
            break;
        case LOG_WARNING:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[WARNING]", sizeof "[WARNING]", 0xFFFF);
            break;
        case LOG_ERROR:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[ERROR]", sizeof "[ERROR]", 0xFFFF);
            break;
        case LOG_FATAL:
            HAL_UART_Transmit(&huart1, (uint8_t *) "[FATAL]", sizeof "[FATAL]", 0xFFFF);
            break;
        default:
            break;
    }
    vprintf(format,args);
    HAL_UART_Transmit(&huart1, (uint8_t *) "\r\n", sizeof "\r\n", 0xFFFF);
    va_end(args);
}
void processCommand(char * str,uint32_t size)
{
    if(strstr(str,"help"))
    {
        HAL_UART_Transmit(&huart1, (uint8_t *) "help: print help message\r\n", sizeof "help: print help message\r\n", 0xFFFF);
    }
}