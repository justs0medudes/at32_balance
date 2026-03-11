#ifndef AT32_BALANCE_V0_1_PERIPH_ENCODER_H
#define AT32_BALANCE_V0_1_PERIPH_ENCODER_H

#include <stdint.h>
uint16_t periph_encoder1_read(void);
uint16_t periph_encoder2_read(void);
void periph_encoder_init(void);
void periph_encoder_handle(void);

typedef struct {
    uint16_t angle;
    int16_t rawdiff;
    float diff;
    float vel;
}encoder_t;

typedef struct {
    encoder_t encoder1;
    encoder_t encoder2;
}ma732_t;
extern ma732_t ma732;
#endif // AT32_BALANCE_V0_1_PERIPH_ENCODER_H