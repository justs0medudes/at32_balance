#ifndef AT32_BALANCE_V0_1_PERIPH_ENCODER_H
#define AT32_BALANCE_V0_1_PERIPH_ENCODER_H

#include <stdint.h>
uint8_t periph_encoder1_data[4];
uint8_t periph_encoder2_data[4];
uint16_t periph_encoder1_read(void);
uint16_t periph_encoder2_read(void);
void periph_encoder_init(void);
void periph_encoder_handle(void);

typedef struct {
    uint16_t angle;
    int16_t diff;
    float vel;
}select_t;

typedef struct {
    select_t encoder1;
    select_t encoder2;
}ma732_t;
extern ma732_t ma732;
#endif // AT32_BALANCE_V0_1_PERIPH_ENCODER_H