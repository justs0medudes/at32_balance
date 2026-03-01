//
// Created by Simon Gong on 2026-02-25.
//

#include "periph_mpu.h"

#include "periph_led.h"
#include "sys_delay.h"
#include "sys_spi.h"
#include "sys_usart.h"

uint8_t periph_mpu_data[14];

uint8_t periph_mpu_write(uint8_t reg, uint8_t data) {
    uint8_t status;
    SPI3_CS0;
    status = sys_spi3_txrx(reg);
    sys_spi3_txrx(data);
    SPI3_CS1;
    return status;
}

uint8_t periph_mpu_read(uint8_t reg) {
    SPI3_CS0;
    uint8_t value;
    sys_spi3_txrx(reg | 0x80);
    value = sys_spi3_txrx(0xFF);
    SPI3_CS1;
    return value;
}

uint8_t who_am_i = 0;
void periph_mpu_init(void) {
    sys_spi3_init();
    for (int i = 0; i < 10; i++) {
        who_am_i = periph_mpu_read(MPU6500_WHO_AM_I);
        delay_ms(1);
    }
    if (who_am_i != 0x70) {
        const char err[] = "MPU failed\r\n";
        sys_usart3_send((uint8_t*)err, strlen(err));
        periph_led_actions(R_LED, LED_ON, 0);
        while (1);
    } else {
        const char gg[] = "MPU ready\r\n";
        sys_usart3_send((uint8_t*)gg, strlen(gg));

        delay_ms(10);
        periph_mpu_write(MPU6500_PWR_MGMT_1, 0x80);
        delay_ms(10);
        periph_mpu_write(MPU6500_PWR_MGMT_1, 0x01);
        delay_ms(10);
        periph_mpu_write(MPU6500_SIGNAL_PATH_RESET, 0x07);
        delay_ms(10);
        periph_mpu_write(MPU6500_CONFIG, 0x00);
        delay_ms(10);
        periph_mpu_write(MPU6500_GYRO_CONFIG, 0x18);
        delay_ms(10);
        periph_mpu_write(MPU6500_ACCEL_CONFIG, 0x10);
        delay_ms(10);
    }
}

void periph_mpu_get(uint8_t *data) {
    SPI3_CS0;
    sys_spi3_txrx(MPU6500_ACCEL_XOUT_H | 0x80);
    for (int i = 0; i < 14; i++) {
        data[i] = sys_spi3_txrx(0xFF);
    }
    SPI3_CS1;
}


mpu6500_t mpu;
void periph_mpu_handle(void) {
    periph_mpu_get(periph_mpu_data);

    // extract raw data
    mpu.acc.raw.x = ((int16_t)periph_mpu_data[0]<<8|periph_mpu_data[1]);
    mpu.acc.raw.y = ((int16_t)periph_mpu_data[2]<<8|periph_mpu_data[3]);
    mpu.acc.raw.z = ((int16_t)periph_mpu_data[4]<<8|periph_mpu_data[5]);
    mpu.gyro.raw.x = ((int16_t)periph_mpu_data[8]<<8|periph_mpu_data[9]);
    mpu.gyro.raw.y = ((int16_t)periph_mpu_data[10]<<8|periph_mpu_data[11]);
    mpu.gyro.raw.z = ((int16_t)periph_mpu_data[12]<<8|periph_mpu_data[13]);

    // scale raw data
    mpu.acc.scale.x = (float)mpu.acc.raw.x / 4096.0f;
    mpu.acc.scale.y = (float)mpu.acc.raw.y / 4096.0f;
    mpu.acc.scale.z = (float)mpu.acc.raw.z / 4096.0f;
    mpu.gyro.scale.x = (float)mpu.gyro.raw.x / 16.4f;
    mpu.gyro.scale.y = (float)mpu.gyro.raw.y / 16.4f;
    mpu.gyro.scale.z = (float)mpu.gyro.raw.z / 16.4f;

    // filter
    mpu.acc.filter.x += (mpu.acc.scale.x - mpu.acc.filter.x) * 0.01f;
    mpu.acc.filter.y += (mpu.acc.scale.y - mpu.acc.filter.y) * 0.01f;
    mpu.acc.filter.z += (mpu.acc.scale.z - mpu.acc.filter.z) * 0.01f;
    mpu.gyro.filter.x += (mpu.gyro.scale.x - mpu.gyro.filter.x) * 0.05f;
    mpu.gyro.filter.y += (mpu.gyro.scale.y - mpu.gyro.filter.y) * 0.05f;
    mpu.gyro.filter.z += (mpu.gyro.scale.z - mpu.gyro.filter.z) * 0.05f;

    // convert
    mpu.acc.angle.x = atan2f(mpu.acc.filter.y, mpu.acc.filter.z)*57.2957795f;
    mpu.acc.angle.y = -atan2f(mpu.acc.filter.x, mpu.acc.filter.z)*57.2957795f;

    mpu.angle.x += mpu.gyro.filter.x * 0.001f;
    mpu.angle.x = mpu.angle.x * 0.999f + mpu.acc.angle.x * 0.001f;
    mpu.angle.y += mpu.gyro.filter.y * 0.001f;
    mpu.angle.y = mpu.angle.y * 0.999f + mpu.acc.angle.y * 0.001f;
}
