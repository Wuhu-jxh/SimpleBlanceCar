//
// Created by 神奇bug在哪里 on 2023/5/4.
//

#include "MPU6050.h"
#include "i2c.h"
#include "SerialIO.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"
void MPU6050::writeByte(uint8_t reg, uint8_t data) const {
    HAL_I2C_Mem_Write(&hi2c1,addr,reg,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
}

uint8_t MPU6050::readByte(uint8_t reg) const {
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1,addr,reg,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
    return data;
}

void MPU6050::readBytes(uint8_t reg, uint8_t *buf, uint8_t len) const {
    HAL_I2C_Mem_Read(&hi2c1,addr,reg,I2C_MEMADD_SIZE_8BIT,buf,len,1000);
}

void MPU6050::update() {
    uint8_t buf[14];
    readBytes(0x3B,buf,14);
    data.accel.x = (buf[0]<<8)|buf[1];
    data.accel.y = (buf[2]<<8)|buf[3];
    data.accel.z = (buf[4]<<8)|buf[5];
    data.temp = (buf[6]<<8)|buf[7];
    data.gyro.x = (buf[8]<<8)|buf[9];
    data.gyro.y = (buf[10]<<8)|buf[11];
    data.gyro.z = (buf[12]<<8)|buf[13];
    sysLogf(LOG_DEBUG,"accel: %d %d %d,gyro: %d %d %d",data.accel.x,data.accel.y,data.accel.z,data.gyro.x,data.gyro.y,data.gyro.z);
}



#pragma clang diagnostic pop