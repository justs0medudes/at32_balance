/*





*/
#include "periph_encoder.h"
#include "sys_spi.h"

#define FILTER_VALUE 0.2f
#define ENC_RAD_C 0.383495f

uint16_t periph_encoder1_read(void) {
    SPI1_0CS0;
    const uint8_t msb = sys_spi1_txrx(0x00);
    const uint8_t lsb = sys_spi1_txrx(0x00);
    SPI1_0CS1;
    const uint16_t raw = (msb << 8) | lsb;
    return (raw >> 2) & 0x3FFF;
}

uint16_t periph_encoder2_read(void) {
    SPI1_1CS0;
    const uint8_t msb = sys_spi1_txrx(0x00);
    const uint8_t lsb = sys_spi1_txrx(0x00);
    SPI1_1CS1;
    const uint16_t raw = (msb << 8) | lsb;
    return (raw >> 2) & 0x3FFF;
}

void periph_encoder_init(void) {
    sys_spi1_init();
    gpio_bits_set(GPIOD, GPIO_PINS_5 | GPIO_PINS_7); // Set CS pins high
}

ma732_t ma732;
static uint16_t encoder1_last = 0;
static uint16_t encoder2_last = 0;
void periph_encoder_handle(void)
{
    const uint16_t now1 = periph_encoder1_read();
    const uint16_t now2 = periph_encoder2_read();

    int16_t diff1 = (int16_t)(now1 - encoder1_last);
    int16_t diff2 = (int16_t)(now2 - encoder2_last);

    if (diff1 > 8192)  diff1 -= 16384;
    if (diff1 < -8192) diff1 += 16384;

    if (diff2 > 8192)  diff2 -= 16384;
    if (diff2 < -8192) diff2 += 16384;

    encoder1_last = now1;
    encoder2_last = now2;

    // putting diff1 and diff2 inside int16_t
    ma732.encoder1.rawdiff = diff1;
    ma732.encoder2.rawdiff = diff2;
    // puts the raw angle data inside uint16_t
    // data format: 0-16383
    ma732.encoder1.rawangle = now1;
    ma732.encoder2.rawangle = now2;
    // rad/s value feeding to the foc library
    ma732.encoder1.diff_rad += (((float)ma732.encoder1.rawdiff * ENC_RAD_C) - ma732.encoder1.diff_rad) * FILTER_VALUE;
    ma732.encoder2.diff_rad += (((float)ma732.encoder2.rawdiff * ENC_RAD_C) - ma732.encoder2.diff_rad) * FILTER_VALUE;
    // difference per 1kHz sample rate in float form
    ma732.encoder1.diff_deg += ((float)ma732.encoder1.rawdiff - ma732.encoder1.diff_deg) * FILTER_VALUE;
    ma732.encoder2.diff_deg += ((float)ma732.encoder2.rawdiff - ma732.encoder2.diff_deg) * FILTER_VALUE;
    // absolute degrees converted to float (used for usart output)
    ma732.encoder1.angle_deg = (float)ma732.encoder1.rawangle;
    ma732.encoder2.angle_deg = (float)ma732.encoder2.rawangle;
}