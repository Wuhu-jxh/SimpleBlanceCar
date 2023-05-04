//
// Created by 神奇bug在哪里 on 2023/5/4.
//

#ifndef SIMPLEBLANCECAR_MPU6050_H
#define SIMPLEBLANCECAR_MPU6050_H
#include "main.h"

class MPU6050 {
private:
    uint16_t addr;
    explicit MPU6050(uint16_t addr)
    {
        this->addr = addr;
    }

};


#endif //SIMPLEBLANCECAR_MPU6050_H
