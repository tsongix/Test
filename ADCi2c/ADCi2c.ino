#include <TinyWireM.h>
#include <USI_TWI_Master.h>
#include <Wire.h>



//#define ADS_ADDRESS_W      0b10010000
//#define ADS_ADDRESS_R     0b10010001
//#define ADS_CONFIG_REGISTER   0b00000001
//#define ADS_CONV_REGISTER   0b00000000
//#define ADS_MSB_CONF_REG    0b11110000    // OS=1, MUX=111(AIN3-GND), PGA=000(FSR=6.144), MODE=0(continuous)
//#define ADS_LSB_CONF_REG    0b11100011    // DR=100(1600SPS), COMP_MODE=0, COMP_POL=0, COMP_LAT=0, COMP_QUE=11(comparator disabled)

uint8_t ADS_ADDRESS_W = 0x48;
uint8_t ADS_ADDRESS_R = 0x49;
uint8_t ADS_CONFIG_REGISTER = 0x01;
uint8_t ADS_CONV_REGISTER = 0x00;
uint8_t ADS_MSB_CONF_REG = 0xF0;         // 0b11110000;    // OS=1, MUX=111(AIN3-GND), PGA=000(FSR=6.144), MODE=0(continuous)
uint8_t ADS_LSB_CONF_REG = 0xE2;             //0b11100011;    // DR=100(1600SPS), COMP_MODE=0, COMP_POL=0, COMP_LAT=0, COMP_QUE=11(comparator disabled)

void setup() {
  Wire.begin();
  Serial.begin(9600);


  Serial.println("init done");
}

void loop() {

  uint8_t msb_conv_reg, lsb_conv_reg;

  Wire.beginTransmission(ADS_ADDRESS_W );
  Wire.write((uint8_t)ADS_CONFIG_REGISTER);
  Wire.write((uint8_t)ADS_MSB_CONF_REG);
  Wire.write((uint8_t)ADS_LSB_CONF_REG);
  Wire.endTransmission();

  //delay(1);

  Wire.beginTransmission(ADS_ADDRESS_W );
  Wire.write(ADS_CONV_REGISTER);
  Wire.endTransmission();

  Wire.requestFrom(ADS_ADDRESS_W, (uint8_t)2);
  
  msb_conv_reg = Wire.read();
  lsb_conv_reg = Wire.read();

  uint16_t conv_r = ((msb_conv_reg << 8) | lsb_conv_reg);
  uint16_t conv_res = conv_r >> 4 ;

  Serial.println(String(conv_res));

  Serial.println();

  //delay(50);
  

}
