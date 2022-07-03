#include "M5Atom.h"
#include <driver/i2s.h>
#include<Arduino.h>

#define CONFIG_I2S_BCK_PIN 19
#define CONFIG_I2S_LRCK_PIN 33
#define CONFIG_I2S_DATA_PIN 22
#define CONFIG_I2S_DATA_IN_PIN 23

#define SPAKER_I2S_NUMBER I2S_NUM_0

extern const unsigned char fanfare[364808];
extern const unsigned char gun[103372];
extern const unsigned char boot[32044];

bool InitI2SSpaker()
{
    esp_err_t err = ESP_OK;

    i2s_driver_uninstall(SPAKER_I2S_NUMBER);
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
        .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 6,
        .dma_buf_len = 60,
    };
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    i2s_config.use_apll = false;
    i2s_config.tx_desc_auto_clear = true;

    err += i2s_driver_install(SPAKER_I2S_NUMBER, &i2s_config, 0, NULL);
    i2s_pin_config_t tx_pin_config;

    tx_pin_config.bck_io_num = CONFIG_I2S_BCK_PIN;
    tx_pin_config.ws_io_num = CONFIG_I2S_LRCK_PIN;
    tx_pin_config.data_out_num = CONFIG_I2S_DATA_PIN;
    tx_pin_config.data_in_num = CONFIG_I2S_DATA_IN_PIN;

    err += i2s_set_pin(SPAKER_I2S_NUMBER, &tx_pin_config);
    err += i2s_set_clk(SPAKER_I2S_NUMBER, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

    return true;
}

size_t bytes_written;

void setup()
{
    M5.begin(true, false, true);
    InitI2SSpaker();
    Serial.begin(115200);
    
}

char key;
    
void loop()
{  
  if(Serial.available()){
    key=Serial.read();
    Serial.write(key);
    if(key=='0'){
      i2s_write(SPAKER_I2S_NUMBER, boot, 32044, &bytes_written, portMAX_DELAY);
    }else if(key=='1'){
      i2s_write(SPAKER_I2S_NUMBER, gun, 103372, &bytes_written, portMAX_DELAY);
    }else if(key=='2'){
      i2s_write(SPAKER_I2S_NUMBER, fanfare, 364808, &bytes_written, portMAX_DELAY);
    }
  }
  if (M5.Btn.isPressed()){
    i2s_write(SPAKER_I2S_NUMBER, gun, 103372, &bytes_written, portMAX_DELAY);
  }
}

/* #define MODE_MIC 0
#define MODE_SPK 1
bool InitI2SSpakerOrMic(int mode)
{
    esp_err_t err = ESP_OK;

    i2s_driver_uninstall(SPAKER_I2S_NUMBER);
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
        .channel_format = I2S_CHANNEL_FMT_ALL_RIGHT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 6,
        .dma_buf_len = 60,
    };
    if (mode == MODE_MIC)
    {
        i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM);
    }
    else
    {
        i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
        i2s_config.use_apll = false;
        i2s_config.tx_desc_auto_clear = true;
    }

    //Serial.println("Init i2s_driver_install");

    err += i2s_driver_install(SPAKER_I2S_NUMBER, &i2s_config, 0, NULL);
    i2s_pin_config_t tx_pin_config;

    tx_pin_config.bck_io_num = CONFIG_I2S_BCK_PIN;
    tx_pin_config.ws_io_num = CONFIG_I2S_LRCK_PIN;
    tx_pin_config.data_out_num = CONFIG_I2S_DATA_PIN;

    //Serial.println("Init i2s_set_pin");
    err += i2s_set_pin(SPAKER_I2S_NUMBER, &tx_pin_config);
    //Serial.println("Init i2s_set_clk");
    err += i2s_set_clk(SPAKER_I2S_NUMBER, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);

    return true;
}

size_t bytes_written;
int count=0;
void setup()
{
    M5.begin(true, false, true);
    InitI2SSpakerOrMic(MODE_SPK);
    Serial.begin(115200);
}
char key;
void loop(){
  if(Serial.available()){
    key=Serial.read();
    Serial.write(key);
    if(key=='0'){
      i2s_write(SPAKER_I2S_NUMBER, boot, 32044, &bytes_written, portMAX_DELAY);
    }else if(key=='1'){
      i2s_write(SPAKER_I2S_NUMBER, gun, 103372, &bytes_written, portMAX_DELAY);
    }else if(key=='2'){
      i2s_write(SPAKER_I2S_NUMBER, fanfare, 364808, &bytes_written, portMAX_DELAY);
    }
  }
  if (M5.Btn.isPressed()){
    M5.dis.drawpix(0, CRGB(0, 0, 128));
      i2s_stop(SPAKER_I2S_NUMBER);
      i2s_start(SPAKER_I2S_NUMBER);
    i2s_write(SPAKER_I2S_NUMBER, gun, 103372, &bytes_written, portMAX_DELAY);
    //i2s_write(SPAKER_I2S_NUMBER, fanfare, 364808, &bytes_written, portMAX_DELAY);
  }
  
  M5.dis.drawpix(0, CRGB(0, 0, 0));
  M5.update();
} */