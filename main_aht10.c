#include <16F877A.h>
#fuses HS, NOWDT, NOPROTECT, NOLVP
#use delay(clock=20MHz)
#use I2C(MASTER, SDA=PIN_C4, SCL=PIN_C3, FAST=100000)  
#use i2c(master, sda=PIN_C4, scl=PIN_C3, stream=SSD1306_STREAM, fast=100000)
#include "SSD1306.c"
#define AHT10_ADDR 0x38
#define SICAK  PIN_B7
#define NORMAL PIN_B5


char degree[] = {0, 7, 5, 7, 0}; 
void aht10_init() {
    i2c_start();
    i2c_write(AHT10_ADDR << 1);
    i2c_write(0xE1);  
    i2c_write(0x08);
    i2c_write(0x00);
    i2c_stop();
    delay_ms(100);
}

void aht10_trigger() {
    i2c_start();
    i2c_write(AHT10_ADDR << 1);
    i2c_write(0xAC);  
    i2c_write(0x33);
    i2c_write(0x00);
    i2c_stop();
}

int8 aht10_is_busy() {
    i2c_start();
    i2c_write((AHT10_ADDR << 1) | 1);
    int8 status = i2c_read(0);  
    i2c_stop();
    return (status & 0x80) ? 1 : 0;
}

void aht10_read(float *temp, float *hum) {
    int8 data[6];
    
    i2c_start();
    i2c_write((AHT10_ADDR << 1) | 1);
    for(int i = 0; i < 5; i++) {
        data[i] = i2c_read(1);  
    }
    data[5] = i2c_read(0);  
    i2c_stop();

    // 20-bit veri çözümleme
    int32 raw_hum = ((int32)data[1] << 12) | ((int32)data[2] << 4) | (data[3] >> 4);
    int32 raw_temp = (((int32)data[3] & 0x0F) << 16) | ((int32)data[4] << 8) | data[5];

    // Dönüþüm formülleri (Datasheet)
    *hum = (raw_hum / 1048576.0) * 100.0;     
    *temp = (raw_temp / 1048576.0) * 200.0 - 50.0;
}



void main(){
   float temperature, humidity; 
   char buffer[20];
   
   SSD1306_Init(SSD1306_SWITCHCAPVCC, 0X78);
   aht10_init();
   
   while(True){
      aht10_trigger();
      delay_ms(80);  
      
      
      if(!aht10_is_busy()) { 
         aht10_read(&temperature, &humidity);
         SSD1306_ClearDisplay();
         
         SSD1306_GotoXY(1, 1);
         printf(SSD1306_PutC, "Dig. Termometre");
         
         //temperature
         SSD1306_GotoXY(1, 3);
         sprintf(buffer, "TEMP: %.2f", temperature);
         printf(SSD1306_PutC, buffer);
         SSD1306_GotoXY(12, 3);
         SSD1306_PutCustomC(degree);
         SSD1306_GotoXY(13, 3);
         printf(SSD1306_PutC, "C");
         //humidity
         SSD1306_GotoXY(1, 5);
         sprintf(buffer, "HUM: %.2f", humidity);
         printf(SSD1306_PutC, buffer);
         
         // Sistem durumu
         SSD1306_GotoXY(1, 7);
         if(temperature < 30.0) {
            printf(SSD1306_PutC, "Ortam Ideal");
            output_high(NORMAL);  // RB5 HIGH (Yeþil LED yanar)
         } else {
            printf(SSD1306_PutC, "Ortam Sicak!"); 
            output_high(SICAK);  // RB7 HIGH (Buzzer öter)
         }
     
      }
      delay_ms(2000);
   }

}
