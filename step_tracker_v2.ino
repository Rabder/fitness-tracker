#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>

Adafruit_MPU6050 mpu;
SoftwareSerial BT(10,11); 

int counter = 0;
float interval[2] = {1, 1};
bool positive = false;
bool negative = false;
int steps = 0;
int calories = 0;

void setup(void) {
  Serial.begin(9600);
  BT.begin(9600);
  BT.println("TIME,STEPS,CALORIES");
  while (!Serial)
    delay(10); // Will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
}

void loop() {

  if (counter < 2){
    sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration x: ");
    Serial.println(a.acceleration.x);
    Serial.println("");
    Serial.print("Acceleration x 0 : ");
    Serial.println(a.acceleration.x);
    Serial.println("");
    Serial.print("Steps: ");
    Serial.println(steps);
    //BT.print("Acceleration x: ");
    //BT.println(a.acceleration.x);
    //BT.println("");
    interval[counter] *= (a.acceleration.x);
    counter++;
  }
  else{

      Serial.print("Interval [0] ");
      Serial.println(interval[0]);
      Serial.print("Interval [1] ");
      Serial.println(interval[1]);
     if (abs(interval[0]-interval[1]) > 0.3){
        steps++;
      }

      counter = 0;
      for (int j=0;j<2;j++){
        interval[j] = 1;
      }
  }
  calories = 0.05 * steps;
  BT.print(",");
  BT.print(steps);
  BT.print(",");
  BT.print(calories);
  BT.println("");
  delay(500);
}
