//
// Created by Simon Gong on 2026-02-25.
//

#ifndef AT32_BALANCE_V0_1_PERIPH_MPU_H
#define AT32_BALANCE_V0_1_PERIPH_MPU_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MPU6500_CONFIG                0x1A
#define MPU6500_GYRO_CONFIG           0x1B
#define MPU6500_ACCEL_CONFIG          0x1C
#define MPU6500_ACCEL_XOUT_H          0x3B

#define MPU6500_ACCEL_XOUT_L          0x3C
#define MPU6500_ACCEL_YOUT_H          0x3D
#define MPU6500_ACCEL_YOUT_L          0x3E
#define MPU6500_ACCEL_ZOUT_H          0x3F
#define MPU6500_ACCEL_ZOUT_L          0x40
#define MPU6500_TEMP_OUT_H            0x41
#define MPU6500_TEMP_OUT_L            0x42
#define MPU6500_GYRO_XOUT_H           0x43
#define MPU6500_GYRO_XOUT_L           0x44
#define MPU6500_GYRO_YOUT_H           0x45
#define MPU6500_GYRO_YOUT_L           0x46
#define MPU6500_GYRO_ZOUT_H           0x47
#define MPU6500_GYRO_ZOUT_L           0x48

#define MPU6500_SIGNAL_PATH_RESET     0x68
#define MPU6500_PWR_MGMT_1            0x6B
#define MPU6500_WHO_AM_I              0x75

typedef struct {
    float x;
    float y;
    float z;
}axisf_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
}axisint_t;

typedef struct {
    axisint_t raw;
    axisf_t scale;
    axisf_t filter;
    axisf_t angle;
}select_t;

typedef struct {
    select_t acc;
    select_t gyro;
    axisf_t angle;
}mpu6500_t;
extern mpu6500_t mpu;
uint8_t periph_mpu_write(uint8_t reg, uint8_t data);
uint8_t periph_mpu_read(uint8_t reg);
void periph_mpu_init(void);
void periph_mpu_get(uint8_t *data);
void periph_mpu_handle(void);

#endif //AT32_BALANCE_V0_1_PERIPH_MPU_H