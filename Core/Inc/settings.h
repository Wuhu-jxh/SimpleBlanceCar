//
// Created by 神奇bug在哪里 on 2023/4/27.
//

#ifndef SIMPLEBLANCECAR_SETTINGS_H
#define SIMPLEBLANCECAR_SETTINGS_H
/*************卡尔曼滤波参数**************/
#define KALMAN_Q 0.02f //测量噪声
#define KALMAN_R 0.5f //过程噪声
#define KALMAN_P 0.0f //协方差
#define KALMAN_K 0.0f //kalman增益
//以下两个参数不应该被修改，因为他们是测量值和过程值。
#define KALMAN_Z 0.0f //测量值
#define KALMAN_U 0.0f //过程值

/*************低通滤波参数**************/
#define LOW_PASS_FILTER_A 0.02f  //低通滤波系数
/*************电机参数**************/
#define MOTOR_MAX 1000

/************PID环_速度环参数*************/
#define SPEED_PID_KP 0.5f
#define SPEED_PID_KI 0.0f
//速度环不应有KD

/************PID环_角度环(转向环)参数*************/
#define ANGLE_PID_KP 0.5f
//角度环不应有KI
//角度环不应有KD

/************PID环_位置环(直立环)参数*************/
#define POSITION_PID_KP 0.5f
//位置环不应有KI
#define POSITION_PID_KD 0.0f
#define POSITION_PID_TARGET 0.0f


#endif //SIMPLEBLANCECAR_SETTINGS_H
