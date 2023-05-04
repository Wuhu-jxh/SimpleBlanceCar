//
// Created by 神奇bug在哪里 on 2023/4/27.
//

#include "pidControl.h"
//卡尔曼滤波函数初始化，具体参照头文件
void kalmanFilter_Init(kalman_filter *kalman, float p, float q, float r, float k, float z, float u)
{

    kalman->p = p;
    kalman->q = q;
    kalman->r = r;
    kalman->k = k;
    kalman->z = z;
    kalman->u = u;
    kalman->x_last = 0;
    kalman->p_last = 0;
    kalman->x_mid = 0;
    kalman->x_now = 0;
    kalman->p_mid = 0;
    kalman->p_now = 0;
}
float KalmanFilter_calc(kalman_filter *kalman, float measure)
{
    //预测
    kalman->x_mid = kalman->x_last + kalman->u;
    kalman->p_mid = kalman->p_last + kalman->q;
    //计算kalman增益
    kalman->k = kalman->p_mid / (kalman->p_mid + kalman->r);
    //修正
    kalman->x_now = kalman->x_mid + kalman->k * (measure - kalman->x_mid);
    //计算最优值的协方差
    kalman->p_now = (1 - kalman->k) * kalman->p_mid;
    //更新上一次的值
    kalman->p_last = kalman->p_now;
    kalman->x_last = kalman->x_now;
    //返回最优化的值
    return kalman->x_now;
}

void pid_Init(PID *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->err = 0;
    pid->err_last = 0;
    pid->integral = 0;
    pid->derivative = 0;
    pid->output = 0;
}

float pid_calc(PID *pid, float target, float measure)
{
    pid->err = target - measure;
    pid->integral += pid->err;
    pid->derivative = pid->err - pid->err_last;
    pid->output = pid->kp * pid->err + pid->ki * pid->integral + pid->kd * pid->derivative;
    pid->err_last = pid->err;
    return pid->output;
}
void lowPassInit(low_pass_filter * low_pass , float a)
{
    low_pass->a = a;
    low_pass->b = 1 - a;
    low_pass->x_last = 0;
    low_pass->x_now = 0;
    low_pass->y_last = 0;
    low_pass->y_now = 0;
}
float lowPassCalc(low_pass_filter * low_pass , float measure)
{
    low_pass->x_now = measure;
    low_pass->y_now = low_pass->a * low_pass->x_now + low_pass->b * low_pass->x_last;
    low_pass->x_last = low_pass->x_now;
    low_pass->y_last = low_pass->y_now;
    return low_pass->y_now;

}