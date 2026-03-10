/*





*/
#include "periph_encoder.h"
#include "sys_spi.h"


uint16_t periph_encoder1_read(void) {
    uint8_t msb, lsb;
    SPI1_0CS0;
    msb = sys_spi1_txrx(0x00);
    lsb = sys_spi1_txrx(0x00);
    SPI1_0CS1;
    return ((msb << 8) | lsb) & 0x3FFF;
}

uint16_t periph_encoder2_read(void) {
    uint8_t msb, lsb;
    SPI1_1CS0;
    msb = sys_spi1_txrx(0x00);
    lsb = sys_spi1_txrx(0x00);
    SPI1_1CS1;
    return ((msb << 8) | lsb) & 0x3FFF;
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
    uint16_t now1 = periph_encoder1_read();
    uint16_t now2 = periph_encoder2_read();

    int16_t diff1 = now1 - encoder1_last;
    int16_t diff2 = now2 - encoder2_last;

    if (diff1 > 8192)  diff1 -= 16384;
    if (diff1 < -8192) diff1 += 16384;

    if (diff2 > 8192)  diff2 -= 16384;
    if (diff2 < -8192) diff2 += 16384;

    encoder1_last = now1;
    encoder2_last = now2;

    ma732.encoder1.diff = diff1;
    ma732.encoder2.diff = diff2;

    ma732.encoder1.angle = now1;
    ma732.encoder2.angle = now2;
    ma732.encoder1.vel += (ma732.encoder1.diff - ma732.encoder1.vel) * 0.2f;
    ma732.encoder2.vel += (ma732.encoder2.diff - ma732.encoder2.vel) * 0.2f;

}