# Arduino Sketch for connecting multiple VL6180x sensors

For Arduino UNO & Pro Mini use

SDA: A4
SCL: A5

*WARNING*: Some sensors require 2.8 V VCC. Connect a step-down regulator e.g. LM317.
For VOUT 2.8 V use R1 of 220 Ohm and R2 220 Ohm + 47 Ohm, respectively.

Also, a level shifter must be used for 2.8 V breakout boards!

In addition to SDA/SCL pins, most sensors have IO0 and IO1 pins. IO0 is the enable pin.

After reset, an arbitrary I2C address can be configured, which differs from the hard-coded
I2C of the sensor.

Thus, it is possible to use multiple sensors without changeing the hard-coded address
 of the module (there are usually no solder pads present for changeing its address).

For connecting more than two modules, uncomment, copy & paste and edit the desired
code blocks.
