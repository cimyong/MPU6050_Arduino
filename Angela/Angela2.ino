/*
Auto:YongXin
Time:2019-12-19 13:23:10
*/

#include <Wire.h> 
#include <MPU6050.h> 
#include <SoftwareSerial.h>// import the serial library
MPU6050 mpu;
unsigned long timer = 0;
unsigned long timer2 = 0;
float timeStep = 0.01;
float pitch = 0;
float roll = 0;
float yaw = 0;
float temp =0;

void setup() 
{
  Serial.begin(115200);
  // 初始化 MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Unable to find a valid MPU6050 sensor, please check the line!");
    delay(500);
  }
  
  mpu.calibrateGyro();   // 启动时校准陀螺仪

  mpu.setThreshold(3); //温度（这里没有使用）
}

void loop()
{
  timer = millis();

  //读取陀螺和温度传感器的值
  Vector norm = mpu.readNormalizeGyro();
  temp = mpu.readTemperature();

  // 计算俯仰、横滚和偏航
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // 打印到控制台
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.print(yaw);
  Serial.print(" Temp = ");
  Serial.print(temp);
  Serial.println(" *C");
  delay((timeStep*1000) - (millis() - timer)); //makes sure we read only at a an interval of 0.01 secounds

  if ((millis()-timer2) > 200)
  send_BT();
}

void send_BT()
{   
  int t;
  int x;
  int y;

  if (roll>-100 && roll<100)
  x = map (roll, -100, 100, 0, 100);

  if (pitch>-100 && pitch<100)
  y = map (pitch, -100, 100, 100, 200);

  if (temp>0 && temp<50)
  t = 200 + int(temp); 

  timer2 = millis();
}
