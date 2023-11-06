#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "driver/spi_master.h"


// à définir
#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  14
#define PIN_NUM_CS   5

spi_device_handle_t InitSPIComm();
void send_cmd(spi_device_handle_t spi, const uint8_t cmd);
void send_data(spi_device_handle_t spi, const uint8_t *data, int len, uint8_t *recbuf);