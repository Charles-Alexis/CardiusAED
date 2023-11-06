#include "ComSPI.h"
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html#_CPPv429spi_device_interface_config_t
// https://github.com/espressif/esp-idf/blob/f3704f027e70a370bed3852f39c2ce48b9e8c7dc/examples/peripherals/spi_master/main/spi_master_example_main.c
spi_device_handle_t InitSPIComm()
{
    spi_device_handle_t spi;
    spi_bus_config_t bus_config={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
    }; 
    spi_device_interface_config_t dev_config={
        .clock_speed_hz=1000000,           //Clock out at 1 MHz
        .mode=0,                                //SPI mode 0
        .spics_io_num=PIN_NUM_CS,               //CS pin
        .queue_size=2
        
        
        
        
        
        
        
        ,                          //We want to be able to queue 2 transactions at a time
        // .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
    };

    //initialisation
    esp_err_t temp;
    temp = spi_bus_initialize(VSPI_HOST,&bus_config, 2);
    assert(temp==ESP_OK);
    
    // Ajouter une device
    temp = spi_bus_add_device(VSPI_HOST,&dev_config,&spi);
    assert(temp==ESP_OK);

    return spi;
}

//Envoyer une commande. Uses spi_device_transmit, which waits until the transfer is complete.
void send_cmd(spi_device_handle_t spi, const uint8_t cmd) 
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                     //Command is 8 bits
    t.tx_buffer=&cmd;               //The data is the cmd itself
    t.user=(void*)0;                //D/C needs to be set to 0
    ret=spi_device_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

//Envoyer une data. Uses spi_device_transmit, which waits until the transfer is complete.
void send_data(spi_device_handle_t spi, const uint8_t *data, int len, uint8_t * rec) 
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(rec,0,4);
    if (len==0) return;             //Pas besoin d'envoyer si le lenght est à 0
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=len*8;                 //Len is in bytes, transaction length is in bits.
    t.rxlength = 4;
    t.tx_buffer = data;               //Data
    t.rx_buffer = rec ;             //ReceivingData
    t.user=(void*)1;                //D/C needs to be set to 1
    ret=spi_device_transmit(spi, &t);  //Transmit!
    t.rx_buffer = rec ;             //ReceivingData
    assert(ret==ESP_OK);            //Should have had no issues.
}

/*
void read_data(spi_device_handle_t spi, const uint8_t *data, int len) 
{
    esp_err_t ret;
    spi_transaction_t t;

    data = t.rx_buffer;               //Data
    ret=spi_device_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}*/

