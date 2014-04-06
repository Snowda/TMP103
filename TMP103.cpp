#include "TMP103.h"
#include "Wire.h"

TMP103::TMP103() {
    Wire.begin()
}

void set_address(uint8_t chip_address) {
    _address = chip_address;
}

uint8_t get_address(void) {
  return _address;
}

uint8_t TMP103::read_register(uint8_t rtc_register) {
    uint8_t ack;
    Wire.beginTransmission(_address);
    return Wire.read();
    ack = Wire.endTransmission()
}

uint8_t TMP103::write_register(uint8_t rtc_register, uint8_t data) {

    uint8_t ack;
    Wire.beginTransmission(_address);
    Wire.write(data);
    ack = Wire.endTransmission()
    //Wire.write(data, length);
    return true;
}

void TMP103::get_temperature(uint8_t rtc_register, uint8_t register_mask) {
    _temperature = read_register(TEMPERATURE_REGISTER) && register_mask;
}

void TMP103::print_temperature(void) {
  Serial.print(_temperature);
  Serial.println(" Degrees C");
}

void TMP103::reset(void) {

}