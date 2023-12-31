#include "Speaker.h"
#include "OmaeWaaa.h"                          // The Wav file stored in memory, should be in folder with this file

//  Global Variables/objects    
    static const i2s_port_t i2s_num = I2S_NUM_0;  // i2s port number
    unsigned const char* TheData;
    uint32_t DataIdx=0;                           // index offset into "TheData" for current  data t send to I2S

    struct WavHeader_Struct
    {
      //   RIFF Section    
      char RIFFSectionID[4];      // Letters "RIFF"
      uint32_t Size;              // Size of entire file less 8
      char RiffFormat[4];         // Letters "WAVE"
      
      //   Format Section    
      char FormatSectionID[4];    // letters "fmt"
      uint32_t FormatSize;        // Size of format section less 8
      uint16_t FormatID;          // 1=uncompressed PCM
      uint16_t NumChannels;       // 1=mono,2=stereo
      uint32_t SampleRate;        // 44100, 16000, 8000 etc.
      uint32_t ByteRate;          // =SampleRate * Channels * (BitsPerSample/8)
      uint16_t BlockAlign;        // =Channels * (BitsPerSample/8), effectivly the size of a single sample for all chans.
      uint16_t BitsPerSample;     // 8,16,24 or 32
    
      // Data Section
      char DataSectionID[4];      // The letters "data"
      uint32_t DataSize;          // Size of the data that follows
    }WavHeader;
    
//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
// I2S configuration structures

static const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 44100,                            // Note, this will be changed later
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // high interrupt priority
    .dma_buf_count = 8,                             // 8 buffers
    .dma_buf_len = 1024,                            // 1K per buffer, so 8K of buffer space
    .use_apll=0,
    .tx_desc_auto_clear= true, 
    .fixed_mclk=-1    
};

// These are the physical wiring connections to our I2S decoder board/chip from the esp32, there are other connections
// required for the chips mentioned at the top (but not to the ESP32), please visit the page mentioned at the top for
// further information regarding these other connections.

static const i2s_pin_config_t pin_config = {
    .bck_io_num = 22,                                 // The bit clock connectiom, goes to pin 27 of ESP32
    .ws_io_num = 4,                                  // Word select, also known as word select or left right clock
    .data_out_num = 21,                               // Data out from the ESP32, connect to DIN on 38357A
    .data_in_num = I2S_PIN_NO_CHANGE                  // we are not interested in I2S data into the ESP32
};

//------------------------------------------------------------------------------------------------------------------------


void setup_Master() {
    gpio_pad_select_gpio(ShutDownAudio);
    gpio_set_direction(ShutDownAudio, GPIO_MODE_OUTPUT); 

    const unsigned char *WavFile=rawData44;
    memcpy(&WavHeader,WavFile,44);                     // Copy the header part of the wav data into our structure

    i2s_driver_install(i2s_num, &i2s_config, 0, NULL);        // ESP32 will allocated resources to run I2S
    i2s_set_pin(i2s_num, &pin_config);                        // Tell it the pins you will be using
    i2s_set_sample_rates(i2s_num, WavHeader.SampleRate);      //set sample rate 
    TheData=WavFile+44;                                       // set to start of data  
}


void play()
{ 
    gpio_set_level(ShutDownAudio, 1);

    while(DataIdx<WavHeader.DataSize)
        {  
            uint8_t Mono[4];                             // This holds the data we actually send to the I2S if mono sound
            const unsigned char *Data;                   // Points to the data we are going to send                                              
            size_t BytesWritten;                         // Returned by the I2S write routine, we are not interested in it

            // The WAV Data could be mono or stereo but always 16 bit, that's a data size of 2 byte or 4 bytes  
            // Unfortunatly I2S only allows stereo, so to send mono we have to send the mono sample on both left and right
            // channels. It's a bit of a faf really!
            if(WavHeader.NumChannels==1)     // mono
            {
                Mono[0]=*(TheData+DataIdx);                 // copy the sample to both left and right samples, this is left
                Mono[1]=*(TheData+DataIdx+1);      
                Mono[2]=*(TheData+DataIdx);                 // Same data to the right channel
                Mono[3]=*(TheData+DataIdx+1);     
                Data=Mono;    
            }
            else                            // stereo
                Data=TheData+DataIdx;
            
            i2s_write(i2s_num,Data,4,&BytesWritten,portMAX_DELAY);
            DataIdx+=WavHeader.BlockAlign;                            // increase the data index to next next sample
        }

    if(DataIdx>=WavHeader.DataSize)               // If we gone past end of data reset back to beginning
        {DataIdx=0;} 

    vTaskDelay(40);
    gpio_set_level(ShutDownAudio, 0);                                
}