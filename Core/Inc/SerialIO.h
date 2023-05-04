//
// Created by 神奇bug在哪里 on 2023/5/4.
//

#ifndef SIMPLEBLANCECAR_SERIALIO_H
#define SIMPLEBLANCECAR_SERIALIO_H

#include <string>
#include "main.h"
enum LOG_level {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL,
    LOG_DISABLE
};
void sysLog(enum LOG_level lv, const char *str); //系统日志
//void sysLog(enum LOG_level lv,std::string dat);
void sysLogf(enum LOG_level lv,char *format,...); //系统日志
void returnPid(); //返回PID数据
void returnEncoder(); //返回编码器数据
void returnMotor(); //返回电机数据
void returnKalman(); //返回卡尔曼滤波数据
void returnLowPassFilter(); //返回低通滤波数据
void processCommand(char * str,uint32_t size);
#endif //SIMPLEBLANCECAR_SERIALIO_H
