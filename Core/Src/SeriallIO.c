#include <stdarg.h>
#include <string.h>
#include "SerialIO.h"
#include "main.h"
#include "stdio.h"
#include "settings.h"
extern char rxBuffer;
extern char RxBuffer[RXBUFFERSIZE];
extern int Uart1_Rx_Cnt;
//
// Created by 神奇bug在哪里 on 2023/5/4.
//
void sysLog(enum LOG_level lv,char *str)
{

    if(lv < SERIAL_LOG_LEVEL)
        return;
    switch (lv)
    {
        case LOG_DEBUG:
            printf("[DEBUG]:%s\n",str);
            break;
        case LOG_INFO:
            printf("[INFO]:%s\r\n",str);
            break;
        case LOG_WARNING:
            printf("[WARNING]:%s\r\n",str);
            break;
        case LOG_ERROR:
            printf("[ERROR]:%s\r\n",str);
            break;
        case LOG_FATAL:
            printf("[FATAL]:%s\r\n",str);
            break;
        default:
            break;
    }
}
void sysLogf(enum LOG_level lv,char *format,...)
{
    if(lv < SERIAL_LOG_LEVEL)
        return;
    va_list args;
    va_start(args,format);
    switch (lv)
    {
        case LOG_DEBUG:
            printf("[DEBUG]:");
        case LOG_INFO:
            printf("[INFO]:");
            break;
        case LOG_WARNING:
            printf("[WARNING]:");
            break;
        case LOG_ERROR:
            printf("[ERROR]:");
            break;
        case LOG_FATAL:
            printf("[FATAL]:");
            break;
        default:
            break;
    }
    vprintf(format,args);
    printf("\r\n");
    va_end(args);
}
void processCommand(char * str,uint32_t size)
{
    char * command = NULL;
    if ((command = strstr(RxBuffer,"help")) != NULL)
    {
        //TODO: 显示帮助菜单
    }
}