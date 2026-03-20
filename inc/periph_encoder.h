#ifndef AT32_BALANCE_V0_1_PERIPH_ENCODER_H
#define AT32_BALANCE_V0_1_PERIPH_ENCODER_H

#include <stdint.h>
#include <stdlib.h>
uint16_t periph_encoder1_read(void);
uint16_t periph_encoder2_read(void);
void periph_encoder_init(void);
void periph_encoder1_handle(void);
void periph_encoder2_handle(void);

typedef struct {
    uint16_t rawangle;
    int16_t rawdiff;
    float angle_rad;
    float angle_deg;
    float diff_rad;
    float diff_deg;
}encoder_t;

typedef struct {
    encoder_t encoder1;
    encoder_t encoder2;
}ma732_t;
extern ma732_t ma732;
#endif // AT32_BALANCE_V0_1_PERIPH_ENCODER_H