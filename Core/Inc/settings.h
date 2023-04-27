//
// Created by 神奇bug在哪里 on 2023/4/27.
//

#ifndef SIMPLEBLANCECAR_SETTINGS_H
#define SIMPLEBLANCECAR_SETTINGS_H
/*************卡尔曼滤波参数**************/
#define KALMAN_Q 0.02f
#define KALMAN_R 0.5f
#define KALMAN_P 0.0f
#define KALMAN_K 0.0f
#define KALMAN_Z 0.0f
#define KALMAN_U 0.0f

/*************电机参数**************/
#define MOTOR_MAX 1000

/************PID环_速度环参数*************/
#define SPEED_PID_KP 0.5f
#define SPEED_PID_KI 0.0f
#define SPEED_PID_KD 0.0f

/************PID环_角度环参数*************/
#define ANGLE_PID_KP 0.5f
#define ANGLE_PID_KI 0.0f
#define ANGLE_PID_KD 0.0f

/************PID环_位置环参数*************/
#define POSITION_PID_KP 0.5f
#define POSITION_PID_KI 0.0f
#define POSITION_PID_KD 0.0f


#endif //SIMPLEBLANCECAR_SETTINGS_H
