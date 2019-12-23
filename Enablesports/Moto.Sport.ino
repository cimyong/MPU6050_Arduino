#include <Wire.h>
#include <MPU6050.h>
 
MPU6050 mpu;
 
void setup()
{
  Serial.begin(115200);
 
  Serial.println("Inicjalizacja MPU6050");
 
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
    Serial.println("Nie mozna znalezc MPU6050 - sprawdz polaczenie!");
    delay(500);
  }
  //额外的加速延迟3ms
  mpu.setAccelPowerOnDelay(MPU6050_DELAY_1MS);
 
  //禁用选定事件的硬件中断
  mpu.setIntFreeFallEnabled(false);  
  mpu.setIntZeroMotionEnabled(false);
  mpu.setIntMotionEnabled(false);
 
  //设置滤波器
  mpu.setDHPFMode(MPU6050_DHPF_5HZ);
 
  //设置运动检测阈值4mg（设置值除以2）
  //设置动作检测持续时间5ms
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(2);
 
  //设置零运动检测阈值8mg（该值除以2）
  //设置零动作检测持续时间2ms
  mpu.setZeroMotionDetectionThreshold(4);
  mpu.setZeroMotionDetectionDuration(2);    
 
  //将引脚4和5设置为低电平。
  //连接到这些输出的LED将发出状态信号
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
 
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);  
}
 
void loop()
{
  Vector rawAccel = mpu.readRawAccel();
  Activites act = mpu.readActivites();
 
  //如果检测到运动，请点亮引脚4上的二极管
  if (act.isActivity)
  {
      Serial.println("YunDong");
    digitalWrite(4, HIGH);
        delay(1000);
  } else
  {
    digitalWrite(4, LOW);
  }
 
  //如果检测到运动，请点亮引脚7上的二极管
  if (act.isInactivity)
  {
      Serial.println("TingZhi");
    digitalWrite(7, HIGH);
  } else
  {
    digitalWrite(7, LOW);
  }
 
  delay(50);
 
  digitalWrite(4, LOW);
}
