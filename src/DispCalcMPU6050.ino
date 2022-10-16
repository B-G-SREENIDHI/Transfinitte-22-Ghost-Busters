#include <Wire.h>

#include <MPU6050_tockn.h>
MPU6050 mpu(Wire);

uint16_t count = 0;
float readings[1000];
float ax, ay, a, t, del, accn, disp, cdisp=0.0, preva, prevd, sd;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);
}
void loop()
{
    mpu.update();
    ax = mpu.getAccX();
    ay = mpu.getAccY();
    a = pow((pow(ax,2) + pow(ay,2)),0.5);
    t = millis();
    
    if (count<=1000)
    {
      readings[count] = a;
      if (count==1000)
      {
        sd = calc_sd(readings);
      }
    }
    else
    {
      del = a - prev;
      if (del > sd)
      {
        accn = a;
        disp = 0.5*accn*pow(t,2);
      }
    }
    cdisp = cdisp + disp;
    Serial.println(cdisp);
    count++;
    prev = a;
}

float calc_sd(float readings[])
{
  float sum = 0.0, mean, SD = 0.0;
  int i;
  for (i = 0; i < 10; ++i)
  {
      sum += readings[i];
  }
  mean = sum / 10;
  for (i = 0; i < 10; ++i) {
      SD += pow(readings[i] - mean, 2);
  }
  return sqrt(SD / 10);
}
