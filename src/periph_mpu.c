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

void periph_mpu_handle(void) {
    periph_mpu_get(periph_mpu_data);

    int16_t ax = (periph_mpu_data[0]<<8|periph_mpu_data[1]);
    int16_t ay = (periph_mpu_data[2]<<8|periph_mpu_data[3]);
    int16_t az = (periph_mpu_data[4]<<8|periph_mpu_data[5]);

    float ax_g = ax / 4096.0f;
    float ay_g = ay / 4096.0f;
    float az_g = az / 4096.0f;

    float roll = (ay_g/az_g)*57.2958f;
    int16_t roll_x100 = (int16_t)(roll * 100.0f);

    char buffer[64];
    sprintf(buffer, "Roll: %d.%02d\r\n", roll_x100 / 100, abs(roll_x100 % 100));
    sys_usart3_send((uint8_t*)buffer, strlen(buffer));
}