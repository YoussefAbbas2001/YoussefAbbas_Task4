/*
Author : Youssef Abbas
Date   : 18/9/2021
About  : Ron Broom Strick
*/
#include <Wire.h>

#define LED 8
#define IMU_ADDRESS 0x68


int16_t x_gyro;
int16_t y_gyro;
int16_t z_gyro;
int32_t x_gyro_offset = 0;
int32_t y_gyro_offset = 0;
int32_t z_gyro_offset = 0;
int32_t n_iterations;


void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT); //Red led to indicate issue
  
  //set IMU configurations
  setImuRegister(0x6B,0x00); //Initializing Sensor
  setImuRegister(0x1B,0x18); //Set Gyro Configurations

  
  calibrationImu(n_iterations); //calibrate IMU
}

void loop()
{
  readImuGyro();   //Read Gyro measurments
  
  if (x_gyro > 60 || y_gyro > 60 || z_gyro > 60)
  {
    digitalWrite(LED,HIGH);
    Serial.println("YOUR POSITION IS UNSTABLE");
  }
  else
  {
    digitalWrite(LED,LOW);
    Serial.println("YOUR POSITION IS STABLE");
  }
}

void setImuRegister(uint8_t reg , uint8_t val)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);  //write address of register 
  Wire.write(val);  //write value of register
  Wire.endTransmission();
}

uint8_t readImu1Byte(uint8_t reg)
{ 
  uint8_t data = 0;                    //var to take data in it
  Wire.beginTransmission(IMU_ADDRESS);  
  Wire.write(reg);                     //pit address of register
  Wire.endTransmission();
  
  Wire.requestFrom(IMU_ADDRESS,1);     //request from slave one byte
  while(Wire.available() < 1);         //delay flow of program till 1 byte is ready
  data = Wire.read();                  //read data
  return data;
}
uint16_t readImu2Byte(uint8_t reg)
{
  uint16_t data = 0;                
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);                    //put address of register
  Wire.endTransmission();             
  Wire.requestFrom(IMU_ADDRESS,2);    //request from slave two byte

  while(Wire.available() < 2);        //delay flow of program till 2 byte is ready
  data = Wire.read()<<8 | Wire.read();//read High byte then shifted then read Low byte
  return data;
}

void readImuGyro()
{
  /*
  fuction to read all Gyro 
  */
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(0x43);
  Wire.endTransmission();

  Wire.requestFrom(IMU_ADDRESS,8);
  while(Wire.available() < 8);
  x_gyro = Wire.read()<<8 | Wire.read(); //nominal value of x_gyro
  y_gyro = Wire.read()<<8 | Wire.read(); //nominal value of y_gyro
  z_gyro = Wire.read()<<8 | Wire.read(); //nominal value of z_gyro

  x_gyro = x_gyro  - x_gyro_offset;   //real value of x_gyro
  y_gyro = y_gyro  - y_gyro_offset;   //real value of y_gyro
  z_gyro = z_gyro  - z_gyro_offset;   //read value of z_gyro
    
}

void calibrationImu(uint32_t n_iterations)
{
  for(int i = 0;i<n_iterations ;i++)
  {
    x_gyro_offset += readImu2Byte(0x43);
    y_gyro_offset += readImu2Byte(0x45);
    z_gyro_offset += readImu2Byte(0x47);  
  }
  x_gyro_offset /= n_iterations;
  y_gyro_offset /= n_iterations;
  z_gyro_offset /= n_iterations;
  
}
