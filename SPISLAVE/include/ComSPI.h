#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "driver/spi_master.h"
#include "driver/spi_slave.h"


// à définir
#define SPI_HANDSHAKE 
#define SPI_PIN_NUM_MISO 2
#define SPI_PIN_NUM_MOSI 4
#define SPI_PIN_NUM_CLK  14
#define SPI_PIN_NUM_CS   16

spi_device_handle_t InitSPICommMaster();
void InitSPICommSlave();
void send_cmd(spi_device_handle_t spi, const uint16_t cmd);
void send_data(spi_device_handle_t spi, const uint8_t *data, int len);