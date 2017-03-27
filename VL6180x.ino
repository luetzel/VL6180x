/*
Author:   M. Luetzelberger
License:  GPL-3.0
Purpose:  Arduino Sketch for controlling multiple VL6180x TOF sensors
Version:  1.0
Date:     2017-02-14
Depends:  Wire.h
Changes:
Notes:

For Arduino UNO & Pro Mini use

SDA: A4
SCL: A5

WARNING: Some sensors require 2.8 V VCC. Connect a step-down regulator e.g. LM317.
For VOUT 2.8 V use R1 of 220 Ohm and R2 220 Ohm + 47 Ohm, respectively.

Also, a level shifter must be used for sensors driven with 2.8 V VCC!

In addition to SDA/SCL pins, most sensord have IO0 and IO1 pins. IO0 the enable pin.

After reset, an arbitrary I2C address can be configured, which differs from the hard-coded
I2C of the sensor. Thus, it is possible to use multiple sensors without changeing the
hard-coded address of the module.
*/

#include <Wire.h>
#include <VL6180X.h>

#define RANGE 1

/* List of adresses for each sensor - after reset the address can be configured */
#define address0 0x20
#define address1 0x22
// #define address2 0x24
// #define address1 0x26
// #define address1 0x28
// #define address1 0x30
// #define address1 0x32

/* These Arduino pins must be wired to the IO0 pin of VL6180x */
int enablePin0 = 11;
int enablePin1 = 10;
//int enablePin2 = 9;
//int enablePin3 = 8;
//int enablePin4 = 7;
//int enablePin5 = 6;
//int enablePin6 = 5;

/* Create a new instance for each sensor */
VL6180X sensor0;
VL6180X sensor1;
//VL6180X sensor2;
//VL6180X sensor3;
//VL6180X sensor4;
//VL6180X sensor5;
//VL6180X sensor6;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Reset all connected sensors
  pinMode(enablePin0,OUTPUT);
  pinMode(enablePin1,OUTPUT);
  //pinMode(enablePin2,OUTPUT);
  //pinMode(enablePin3,OUTPUT);
  //pinMode(enablePin4,OUTPUT);
  //pinMode(enablePin5,OUTPUT);
  //pinMode(enablePin6,OUTPUT);
  
  digitalWrite(enablePin0, LOW);
  digitalWrite(enablePin1, LOW);
  //digitalWrite(enablePin2, LOW);
  //digitalWrite(enablePin3, LOW);
  //digitalWrite(enablePin4, LOW);
  //digitalWrite(enablePin5, LOW);
  //digitalWrite(enablePin6, LOW);
  
  delay(1000);
  
  // Sensor0
  Serial.println("Start Sensor 0");
  digitalWrite(enablePin0, HIGH);
  delay(50);
  sensor0.init();
  sensor0.configureDefault();
  sensor0.setAddress(address0);
  Serial.println(sensor0.readReg(0x212),HEX); // read I2C address
  sensor0.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor0.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor0.setTimeout(500);
  sensor0.stopContinuous();
  sensor0.setScaling(RANGE); // configure range or precision 1, 2 oder 3 mm
  delay(300);
  sensor0.startInterleavedContinuous(100);
  delay(100);
  
  // Sensor1
  Serial.println("Start Sensor 1");
  digitalWrite(enablePin1, HIGH);
  delay(50);
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setAddress(address1);
  Serial.println(sensor1.readReg(0x212),HEX);
  sensor1.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor1.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor1.setTimeout(500);
  sensor1.stopContinuous();
  sensor1.setScaling(RANGE);
  delay(300);
  sensor1.startInterleavedContinuous(100);
  delay(100);

//  Sensor2
//  Serial.println("Start Sensor 2");
//  digitalWrite(enablePin2, HIGH);
//  delay(50);
//  sensor2.init();
//  sensor2.configureDefault();
//  sensor2.setAddress(address2);
//  Serial.println(sensor2.readReg(0x212),HEX);
//  sensor2.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
//  sensor2.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
//  sensor2.setTimeout(500);
//  sensor2.stopContinuous();
//  sensor2.setScaling(RANGE);
//  delay(300);
//  sensor2.startInterleavedContinuous(100);
  
  // copy & paste as much sensors as you require
  
  delay(1000);
 
  Serial.println("Sensors ready! Start reading sensors in 3 seconds ...!");
  delay(3000);
}

void loop()
{
  // Read daylight (LUX)
  //Serial.print("\tDaylight0: ");
  //Serial.print(sensor0.readAmbientContinuous());
  //if (sensor0.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  //Serial.print("\tDaylight1: ");
  //Serial.print(sensor1.readAmbientContinuous());
  //if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  //Serial.print("\tDaylight2: ");
  //Serial.print(sensor1.readAmbientContinuous());
  //if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

  // Abstand in mm
  Serial.print("\tDistance0: ");
  Serial.print(sensor0.readRangeContinuousMillimeters());
  if (sensor0.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.print("\tDistance1: ");
  Serial.print(sensor1.readRangeContinuousMillimeters());
  if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

//  Serial.print("\tDistance2: ");
//  Serial.print(sensor2.readRangeContinuousMillimeters());
//  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

// copy & paste as much sensors as you require

  Serial.println();
  
  delay(100);
}
