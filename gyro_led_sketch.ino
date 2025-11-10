/*--------------------------------------------------------------------------------
 * Title : MPU6050 Gyro to MAX7219 LED Matrix Position Indicator
 * Author: Azmaeen Kaikobad
 --------------------------------------------------------------------------------*/

/* --------------------------------- Libraries --------------------------------- */
#include <Wire.h> // Arduino I2C Library
#include <Adafruit_MPU6050.h> // driver for the MPU 6050
#include <Adafruit_Sensor.h> // for standard data types used by sensors
#include <LedControl.h> // library for MAX7219

/* ------------------------------- Initialization ------------------------------ */
Adafruit_MPU6050 mpu;
LedControl lc = LedControl(11, 13, 10, 1); // DIN, CLK, CS wiring

/* --------------------------------  Variables --------------------------------- */
const float gLimit = 9.80665f; // expected abs. value of accel. due to gravity
int lastX = -1, lastY = -1; // stores LED x & y positions

/* -------------------------- MAX 7219 & MPU6050 Setup ------------------------- */
void setup() {

  Serial.begin(115200);
  while (!Serial) { delay(10); } 

  //initializes I2C
  Wire.begin();

  // initializing MAX7219 LED matrix
  lc.shutdown(0, false);    // wakes up the LED matrix
  lc.setIntensity(0, 8);    // brightness level of 8
  lc.clearDisplay(0);       // clears the LED matrix initially

  // initializing MPU6050 Gyro
  Serial.println(F("Initializing MPU6050"));
  if (!mpu.begin()) {
    Serial.println(F("Failed to initialize MPU6050!")); // if initialization fails
    while (1) { delay(100); } // infinite halt; delay removes unnecesary CPU usage
  }
  Serial.println(F("MPU6050 initialized!")); // if initialization succeeds

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);    // accelerometer range set to ±2G
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);         // narrow range for higher sensitivity
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);      // built in DLPF for MPU6050; filters out random impulses
}

/* -------------------  Collecting Data and Mapping Function ------------------- */
void loop() {

  sensors_event_t a, g, temp; // accelerometer, gyroscope, temperature
  mpu.getEvent(&a, &g, &temp);

  // copies accelerometer readings into floats
  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;

  // mapping floats to the LED 8x8
  int gridX = constrain((int)roundf(mapFloat(ax, -gLimit, gLimit, 0, 7)), 0, 7); // using constrain ensures the LED x-coordinates stay in [0,7]
  int gridY = constrain((int)roundf(mapFloat(ay, -gLimit, gLimit, 0, 7)), 0, 7); // using constrain ensures the LED y-coordinates stay in [0,7]

  // debounce mechanism; ensures that the LED updates without any flicker
  if (gridX != lastX || gridY != lastY || lastX == -1) {
    lc.clearDisplay(0);
    lc.setLed(0, gridY, gridX, true); 
    lastX = gridX;
    lastY = gridY;
  }


  delay(100); // update every 100ms
}

/* -------------------------  Float Mapping Function  ------------------------- */
// map() function but for floats; Arduino map() only works for integers
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  if (in_min == in_max) return out_min;
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
