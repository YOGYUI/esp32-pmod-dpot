#ifndef _DEFINITION_H_
#define _DEFINITION_H_
#pragma once

// SPI setting
#define DPOT_SPI_HOST       HSPI_HOST
#define PIN_DPOT_SPI_MOSI   13
#define PIN_DPOT_SPI_MISO   12
#define PIN_DPOT_SPI_SCLK   14
#define PIN_DPOT_SPI_CS     15

#define DPOT_RAB_RESISTANCE 10000   // AD5160 resistance between A-B terminal, 10Kohm
#define DPOT_RW_RESISTANCE  60      // AD5160 wiper resistance

#define WEB_SERVER_PORT     80
#define WIFI_SSID           "YOGYUI-ESP32-TEST"

#endif
