//
// Created by Simon Gong on 2026-02-25.
//

#include "sys_spi.h"

#include "at32f403a_407_spi.h"
#include "sys_delay.h"

void sys_spi3_init(void) {
    spi_enable(SPI3, FALSE);
    spi_init_type spi_init_struct;
    spi_default_para_init(&spi_init_struct);

    spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
    spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
    spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_4;
    spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
    spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
    spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;
    spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
    spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
    spi_init(SPI3, &spi_init_struct);

    spi_enable(SPI3, TRUE);
    delay_ms(10);

    SPI3_CS1; // Important here because floating CS pin can cause the low signal to not be recognized
}

uint8_t sys_spi3_txrx(uint8_t data)
{
    uint8_t cnt=0;
    while(spi_i2s_flag_get(SPI3, SPI_I2S_TDBE_FLAG) == RESET) //等待SPI发送标志位空
    {
        cnt++;
        if(cnt>200)return 0;
    }
    SPI3->dt = data;

    cnt=0;

    while(spi_i2s_flag_get(SPI3, SPI_I2S_RDBF_FLAG) == RESET) //等待SPI接收标志位空
    {
        cnt++;
        if(cnt>200)return 0;
    }
    return SPI3->dt; //接收数据
}