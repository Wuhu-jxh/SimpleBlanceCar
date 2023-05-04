//
// Created by 神奇bug在哪里 on 2023/5/3.
//
#include "main.h"
extern int32_t encoderLeft;
extern int32_t encoderRight;
void encoderUpdate() //更新编码器的值(如果需要)
{
    //读取编码器的值
    encoderLeft = TIM2->CNT;
    encoderRight = TIM3->CNT;
    //清空编码器的值
    TIM2->CNT = 0;
    TIM3->CNT = 0;
}
float encoderSpeedCal() //根据编码器的值并且转换成速度
{
    static float Encoder_Least,Encoder;
    Encoder_Least =(float )(encoderLeft+encoderRight)-0;
    Encoder *= 0.7f;
    Encoder += Encoder_Least*0.3f;
    return  Encoder;
}