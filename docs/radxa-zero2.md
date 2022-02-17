Radxa Zero 2 Single Board Computer    {#radxa-zero2}
=============================

Radxa Zero 2 is an Amlogic A311D based SBC(Single Board Computer) by Radxa. It can run android or some Linux distributions. ROCK Pi 4 features a six core ARM processor, 4GB LPDDR4, up to 4K@60 HDMI, MIPI DSI, MIPI CSI, 802.11 ac WIFI, Bluetooth 5.0, USB Port, 40-pin color expansion header, and NPU.

Board Support
-------------

- [Radxa Zero 2](https://wiki.radxa.com/Zero2)

Interface notes
---------------

- Placeholder since the board is not final yet.

Pin Mapping
-----------

Radxa Zero 2 has a 40-pin expansion header. Each pin is distinguished by color.

|Additional Function |  Primary Function|  PIN  |  PIN  |  Primary Function  | Additional Function |
|--------------------|------------------|:------|------:|--------------------|---------------------|
|                    |   +3.3V          |   1   |   2   |   +5.0V            |                     |
|                    |   I2C_EE_M3_SDA  |   3   |   4   |   +5.0V            |                     |
|                    |   I2C_EE_M3_SCL  |   5   |   6   |   GND              |                     |
|                    |   PWM_D          |   7   |   8   |   UART_AO_A_TX     |                     |
|                    |   GND            |   9   |   10  |   UART_AO_A_RX     |                     |
|                    |   GPIOZ_3        |   11  |   12  |   GPIOA_1          |                     |
|                    |   GPIOZ_4        |   13  |   14  |   GND              |                     |
|                    |   GPIOZ_5        |   15  |   16  |   NC               |                     |
|                    |   +3.3V          |   17  |   18  |   GPIOZ_6          |                     |
|      UART_EE_C_RTS |   SPI_B_MOSI     |   19  |   20  |   GND              |                     |
|PWM_F,UART_EE_C_CTS |   SPI_B_MISO     |   21  |   22  |   SARADC_CH3       |                     |
|PWM_B,I2C_EE_M1_SCL,UART_EE_C_TX|SPI_B_SCLK|23 |   24  |   SPI_B_SS0        |I2C_EE_M1_SDA,UART_EE_C_RX|
|                    |   GND            |   25  |   26  |   SARADC_CH2       |                     |
|              PWM_B |   I2C_EE_M0_SDA  |   27  |   28  |   I2C_EE_M0_SCL    | PWM_C               |
|                    |   GPIOAO_7       |   29  |   30  |   GND              |                     |
|                    |   GPIOA_13       |   31  |   32  |   GPIOA_0          |                     |
|                    |   UART_AO_B_TX   |   33  |   34  |   GND              |                     |
|                    |   GPIOA_2        |   35  |   36  |   GPIOC_7          |                     |
|                    |   UART_AO_B_RX   |   37  |   38  |   GPIOA_5          |                     |
|                    |   GND            |   39  |   40  |   I2C_EE_M0_SDA    |                     |

Resources
---------

The following links will take you to additional Radxa Zero 2 resources

- [Forums](https://forum.radxa.com/c/zero)
- [Github Repo](https://github.com/radxa)
