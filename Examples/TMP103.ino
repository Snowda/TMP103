// Demonstration Arduino sketch for TMP103 Temperature Sensor
// 4/4/2013 original by Conor Forde <me@conorforde.com> at https://github.com/Snowda/TMP103
//
// Changelog:
//     04-04-2014 - initial commit
//
// TMP103 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project

#include "TMP103.h"

TMP103 temperature;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    temperature.set_address(TMP103A);
    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(19200);

    // initialize device
    Serial.println("Initializing Temperature...");
    //temperature.init();

    // verify connection
    //Serial.println("Testing device connections...");
    //Serial.println(temperature.testConnection() ? "TMP103 connection successful" : "TMP103 connection failed");

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // get temperature from device
    temperature.get_temperature();
    //print the recieved measurements
    temperature.print_temperature();

    // other available methods:
    //temperature.set_speed(HIGH_SPEED_COMMAND);

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}