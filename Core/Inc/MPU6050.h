//
// Created by 神奇bug在哪里 on 2023/5/4.
//

#ifndef SIMPLEBLANCECAR_MPU6050_H
#define SIMPLEBLANCECAR_MPU6050_H
#include "main.h"
//MPU的加速度计的数据
typedef struct {
    int32_t x;
    int32_t y;
    int32_t z;
}accel_t;
//MPU的陀螺仪的数据
typedef struct {
    int32_t x;
    int32_t y;
    int32_t z;
}gyro_t;
typedef struct {
    accel_t accel{};  //加速度计
    gyro_t gyro{};  //陀螺仪
    int temp;//MPU6050的温度
}MPU6050_t;
class MPU6050 {
private:
    uint16_t addr;
    MPU6050_t data;

protected:
    void writeByte(uint8_t reg,uint8_t data) const;
    uint8_t readByte(uint8_t reg) const;
    void readBytes(uint8_t reg,uint8_t *buf,uint8_t len) const;
public:
    explicit MPU6050(uint16_t addr)
    {
        this->addr = addr;
        data.accel = {0,0,0};
        data.gyro = {0,0,0};
        data.temp = 0;
        update();
    }
    MPU6050_t getData() const {return data;}
    void update();

};


#endif //SIMPLEBLANCECAR_MPU6050_H
