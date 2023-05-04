//
// Created by 神奇bug在哪里 on 2023/4/27.
//

#ifndef SIMPLEBLANCECAR_PIDCONTROL_H
#define SIMPLEBLANCECAR_PIDCONTROL_H
/*************卡尔曼滤波部分开始**************/

/**
 * @brief 卡尔曼滤波函数
 * @param p 协方差
 * @param q 测量噪声
 * @param r 过程噪声
 * @param k kalman增益
 * @param z 测量值
 * @param u 过程值
 * @return 卡尔曼滤波后的值
 * @note 该函数用于对测量值进行滤波
 */
typedef struct{
    float p; //协方差
    float q; //测量噪声
    float r; //过程噪声
    float k; //kalman增益
    float z; //测量值
    float u; //过程值
    float x_last; //上次的状态值
    float p_last; //上次的协方差
    float x_mid; //估计的误差协方差
    float x_now; //当前的状态值
    float p_mid; //估计的误差协方差
    float p_now; //当前的协方差

} kalman_filter;
/**
 * @brief 卡尔曼滤波初始化函数
 * @param kalman 卡尔曼滤波器参数的结构体地址
 * @param p 协方差
 * @param q 测量噪声
 * @param r 过程噪声
 * @param k kalman增益
 * @param z 测量值
 * @param u 过程值
 */
void kalmanFilter_Init(kalman_filter *kalman, float p, float q, float r, float k, float z, float u);
/**
 * @brief 卡尔曼滤波计算函数
 * @param kalman 卡尔曼滤波器参数的结构体地址
 * @param measure 测量值
 * @return 滤波结果
 * @note 该函数用于对测量值进行滤波，具体实现对应着
 */
float KalmanFilter_calc(kalman_filter *kalman, float measure);
/*
 * 补充信息:
 * 卡尔曼滤波是一种递归贝叶斯滤波算法，它通过一组数学方程来估计一个动态系统的状态。
 * 这些方程包括状态预测方程和观测更新方程。状态预测方程用于预测系统的下一个状态，观测更新方程用于根据观测数据来更新状态估计。
 * 下面是卡尔曼滤波的基本数学公式：
 * 状态预测方程：x’ = Ax + Bu
 * 协方差预测方程：P’ = APA^T + Q
 * 观测残差计算：y = z - Hx’
 * 残差协方差计算：S = HPH^T + R
 * 卡尔曼增益计算：K = PHTS(-1)
 * 状态更新方程：x = x’ + Ky
 * 协方差更新方程：P = (I - KH)P
 * 参考链接 https://cloud.tencent.com/developer/article/2037561
 * @@@ 注意: 本套算法没有完全按照卡尔曼滤波的数学公式来实现，而是根据实际情况进行了一些简化，具体参照代码
 */
/*************卡尔曼滤波部分结束**************/
/*************低通滤波部分开始**************/
typedef struct {
    float a; //低通滤波系数
    float b; //低通滤波系数
    float x_last; //上次的值
    float y_last; //上次的值
    float x_now; //当前的值
    float y_now; //当前的值
} low_pass_filter;
/**
 * @brief 低通滤波初始化函数
 * @param low_pass 低通滤波器参数的结构体地址
 * @param a 低通滤波系数
 */
void lowPassInit(low_pass_filter * low_pass , float a);
/**
 * @brief 低通滤波计算函数
 * @param low_pass 低通滤波器参数的结构体地址
 * @param measure 测量值
 * @return 滤波结果
 */
float lowPassCalc(low_pass_filter * low_pass , float measure);
/*************低通滤波部分结束**************/

/*************PID控制部分开始**************/
//PID参数结构体
typedef struct{
    float kp; //比例系数
    float ki; //积分系数
    float kd; //微分系数
    float err; //误差
    float err_last; //上次的误差
    float integral; //积分值
    float derivative; //微分值
    float output; //输出值
} PID;
/**
 * @brief PID控制器初始化函数
 * @param pid PID控制器参数的结构体地址
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 */
void pid_Init(PID *pid, float kp, float ki, float kd);
/**
 * @brief PID控制器计算函数
 * @param pid PID控制器参数的结构体地址
 * @param target 目标值
 * @param measure 测量值
 * @return PID控制器输出值
 */
float pid_calc(PID *pid, float target, float measure);
/*************PID控制部分结束**************/



#endif //SIMPLEBLANCECAR_PIDCONTROL_H
