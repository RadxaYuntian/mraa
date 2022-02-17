/*
 * Author: Ken <ken@radxa.com>
 *         Yuntian Zhang <yt@radxa.com>
 * Copyright (c) Radxa Limited.
 *
 * SPDX-License-Identifier: MIT
 */

#include <mraa/common.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "arm/radxa_zero2.h"
#include "common.h"

#define DT_BASE "/proc/device-tree"

#define PLATFORM_NAME_RADXA_ZERO2 "Radxa Zero2"

#define MAX_SIZE 64

const char* radxa_zero2_serialdev[MRAA_RADXA_ZERO2_UART_COUNT] = { "/dev/ttyAML0", "/dev/ttyAML6", "/dev/ttyAML7" };

#define GPIOAO(x)   (412 + x)
#define GPIOE(x)    (424 + x)
#define GPIOZ(x)    (427 + x)
#define GPIOH(x)    (443 + x)
#define BOOT(x)     (542 + x)
#define GPIOC(x)    (468 + x)
#define GPIOA(x)    (476 + x)
#define GPIOX(x)    (492 + x)

void
mraa_radxa_zero2_pininfo(mraa_board_t* board, int index, int sysfs_pin, mraa_pincapabilities_t pincapabilities_t, char* fmt, ...)
{
    va_list arg_ptr;

    if (index > board->phy_pin_count)
        return;

    mraa_pininfo_t* pininfo = &board->pins[index];
    va_start(arg_ptr, fmt);
    vsnprintf(pininfo->name, MRAA_PIN_NAME_SIZE, fmt, arg_ptr);

    if( pincapabilities_t.gpio == 1 ) {
        va_arg(arg_ptr, int);
        pininfo->gpio.gpio_chip = va_arg(arg_ptr, int);
        pininfo->gpio.gpio_line = va_arg(arg_ptr, int);
    }

    pininfo->capabilities = pincapabilities_t;

    va_end(arg_ptr);
    pininfo->gpio.pinmap = sysfs_pin;
    pininfo->gpio.mux_total = 0;
}

mraa_board_t*
mraa_radxa_zero2()
{
    mraa_board_t* b = (mraa_board_t*) calloc(1, sizeof(mraa_board_t));
    if (b== NULL) {
        return NULL;
    }

    b->adv_func = (mraa_adv_func_t*) calloc(1, sizeof(mraa_adv_func_t));
    if (b->adv_func == NULL) {
        free(b);
        return NULL;
    }

    // pin mux for buses are setup by default by kernel so tell mraa to ignore them
    b->no_bus_mux = 1;
    b->phy_pin_count = MRAA_RADXA_ZERO2_PIN_COUNT + 1;

    if (mraa_file_exist(DT_BASE "/model")) {
        // We are on a modern kernel, great!!!!
        if (mraa_file_contains(DT_BASE "/model", PLATFORM_NAME_RADXA_ZERO2)  ) {
            b->platform_name = PLATFORM_NAME_RADXA_ZERO2;
            b->uart_dev[0].device_path = (char*) radxa_zero2_serialdev[0];
            b->uart_dev[1].device_path = (char*) radxa_zero2_serialdev[1];
            b->uart_dev[2].device_path = (char*) radxa_zero2_serialdev[2];
        }
    }

    // UART
    b->uart_dev_count = MRAA_RADXA_ZERO2_UART_COUNT;
    b->def_uart_dev = 0;
    b->uart_dev[0].index = 0;
    b->uart_dev[1].index = 1;
    b->uart_dev[2].index = 2;

    // I2C
    if (strncmp(b->platform_name, PLATFORM_NAME_RADXA_ZERO2, MAX_SIZE) == 0) {
        b->i2c_bus_count = MRAA_RADXA_ZERO2_I2C_COUNT ;
        b->def_i2c_bus = 0;
        b->i2c_bus[0].bus_id = 0;
        b->i2c_bus[1].bus_id = 1;
        b->i2c_bus[2].bus_id = 3;
    }

    // SPI
    b->spi_bus_count = MRAA_RADXA_ZERO2_SPI_COUNT;
    b->def_spi_bus = 0;
    b->spi_bus[0].bus_id = 1;

    // PWM
    b->pwm_dev_count = MRAA_RADXA_ZERO2_PWM_COUNT;
    b->pwm_default_period = 500;
    b->pwm_max_period = 2147483;
    b->pwm_min_period = 1;

    b->pins = (mraa_pininfo_t*) malloc(sizeof(mraa_pininfo_t) * b->phy_pin_count);
    if (b->pins == NULL) {
        free(b->adv_func);
        free(b);
        return NULL;
    }

    b->pins[7].pwm.parent_id = 4;
    b->pins[7].pwm.mux_total = 0;
    b->pins[7].pwm.pinmap = 1;
    b->pins[21].pwm.parent_id = 2;
    b->pins[21].pwm.mux_total = 0;
    b->pins[21].pwm.pinmap = 1;
    b->pins[23].pwm.parent_id = 6;
    b->pins[23].pwm.mux_total = 0;
    b->pins[23].pwm.pinmap = 1;
    b->pins[27].pwm.parent_id = 6;
    b->pins[27].pwm.mux_total = 0;
    b->pins[27].pwm.pinmap = 1;
    b->pins[28].pwm.parent_id = 4;
    b->pins[28].pwm.mux_total = 0;
    b->pins[28].pwm.pinmap = 0;
  
    mraa_radxa_zero2_pininfo(b, 0,         -1, (mraa_pincapabilities_t){0,0,0,0,0,0,0,0}, "INVALID");
    mraa_radxa_zero2_pininfo(b, 1,         -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "3V3");
    mraa_radxa_zero2_pininfo(b, 2,         -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "5V");
    mraa_radxa_zero2_pininfo(b, 3,  GPIOA(14), (mraa_pincapabilities_t){1,1,0,0,0,1,0,0}, "I2C_EE_M3_SDA");
    mraa_radxa_zero2_pininfo(b, 4,         -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "5V");
    mraa_radxa_zero2_pininfo(b, 5,  GPIOA(15), (mraa_pincapabilities_t){1,1,0,0,0,1,0,0}, "I2C_EE_M3_SCL");
    mraa_radxa_zero2_pininfo(b, 6,         -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 7,   GPIOZ(2), (mraa_pincapabilities_t){1,1,1,0,0,0,0,0}, "PWM_D");
    mraa_radxa_zero2_pininfo(b, 8,  GPIOAO(0), (mraa_pincapabilities_t){1,1,0,0,0,0,0,1}, "UART_AO_A_TXD");
    mraa_radxa_zero2_pininfo(b, 9,         -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 10, GPIOAO(1), (mraa_pincapabilities_t){1,1,0,0,0,0,0,1}, "UART_AO_A_RXD");
    mraa_radxa_zero2_pininfo(b, 11,  GPIOZ(3), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOZ_3");
    mraa_radxa_zero2_pininfo(b, 12,  GPIOA(1), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOA_1");
    mraa_radxa_zero2_pininfo(b, 13,  GPIOZ(4), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOZ_4");
    mraa_radxa_zero2_pininfo(b, 14,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 15,  GPIOZ(5), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOZ_5");
    mraa_radxa_zero2_pininfo(b, 16,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "NC");
    mraa_radxa_zero2_pininfo(b, 17,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "3V3");
    mraa_radxa_zero2_pininfo(b, 18,  GPIOZ(6), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOZ_6");
    mraa_radxa_zero2_pininfo(b, 19,  GPIOH(4), (mraa_pincapabilities_t){1,1,0,0,1,0,0,1}, "SPI_B_MOSI,UART_EE_C_RTS");
    mraa_radxa_zero2_pininfo(b, 20,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 21,  GPIOH(5), (mraa_pincapabilities_t){1,1,1,0,1,0,0,1}, "PWM_F,SPI_B_MISO,UART_EE_C_CTS");
    mraa_radxa_zero2_pininfo(b, 22,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "SARADC_CH3");
    mraa_radxa_zero2_pininfo(b, 23,  GPIOH(7), (mraa_pincapabilities_t){1,1,1,0,1,1,0,1}, "PWM_B,I2C_EE_M1_SCL,SPI_B_SCLK,UART_EE_C_TX ");
    mraa_radxa_zero2_pininfo(b, 24,  GPIOH(6), (mraa_pincapabilities_t){1,1,0,0,1,1,0,1}, "UART_EE_C_RX,SPI_B_SS0,I2C_EE_M1_SDA");
    mraa_radxa_zero2_pininfo(b, 25,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 26,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "SARADC_CH2");
    mraa_radxa_zero2_pininfo(b, 27,  GPIOZ(0), (mraa_pincapabilities_t){1,1,1,0,0,1,0,0}, "PWM_B,I2C_EE_M0_SDA");
    mraa_radxa_zero2_pininfo(b, 28,  GPIOZ(1), (mraa_pincapabilities_t){1,1,1,0,0,1,0,0}, "I2C_EE_M0_SCL,PWM_C");
    mraa_radxa_zero2_pininfo(b, 29, GPIOAO(7), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOAO_7");
    mraa_radxa_zero2_pininfo(b, 30,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 31, GPIOA(13), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOA_13");
    mraa_radxa_zero2_pininfo(b, 32,  GPIOA(0), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOA_0");
    mraa_radxa_zero2_pininfo(b, 33, GPIOAO(8), (mraa_pincapabilities_t){1,1,0,0,0,0,0,1}, "UART_AO_B_TX");
    mraa_radxa_zero2_pininfo(b, 34,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 35,  GPIOA(2), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOA_2");
    mraa_radxa_zero2_pininfo(b, 36,  GPIOC(7), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOC_7");
    mraa_radxa_zero2_pininfo(b, 37, GPIOAO(9), (mraa_pincapabilities_t){1,1,0,0,0,0,0,1}, "UART_AO_B_RX");
    mraa_radxa_zero2_pininfo(b, 38,  GPIOA(5), (mraa_pincapabilities_t){1,1,0,0,0,0,0,0}, "GPIOA_5");
    mraa_radxa_zero2_pininfo(b, 39,        -1, (mraa_pincapabilities_t){1,0,0,0,0,0,0,0}, "GND");
    mraa_radxa_zero2_pininfo(b, 40,  GPIOZ(7), (mraa_pincapabilities_t){1,1,0,0,0,1,0,0}, "I2C_EE_M0_SDA");

    return b;
}