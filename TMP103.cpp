#include "TMP103.h"
#include "Wire.h"
#include "Math.h"

TMP103::TMP103() {
    Wire.begin();
    _config_status = 0x02; //hardware reset value
}

void set_address(uint8_t chip_address) {
    _address = chip_address;
}

uint8_t get_address(void) {
  return _address;
}

uint8_t TMP103::read_register(uint8_t temp_register) {
    uint8_t ack;
    Wire.beginTransmission(_address);
    Wire.write(temp_register);
    returned_address = Wire.read();
    returned_data = Wire.read();
    ack = Wire.endTransmission();
    return returned_data;
}

uint8_t TMP103::write_register(uint8_t temp_register, uint8_t data) {

    uint8_t ack;
    Wire.beginTransmission(_address);
    Wire.write(temp_register);
    Wire.write(data);
    ack = Wire.endTransmission();
    //Wire.write(data, length);
    return true;
}

void TMP103::get_temperature(void) {
    int8_t raw_reading, calcd_reading;
    raw_reading = read_register(TEMPERATURE_REGISTER) && register_mask;
    if(raw_reading & 0x80) {
        //calculate two's complement - todo
        calcd_reading = raw_reading;
    } else {
        calcd_reading = raw_reading;
    }
    _temperature = fmax(fmin(MAX_TEMPERATURE, calcd_reading), MIN_TEMPERATURE);
}

void TMP103::print_temperature(void) {
  Serial.print(_temperature);
  Serial.println(" Degrees C");
}

void TMP103::reset(void) {
    //pull the scl line low for 30ms
}

void TMP103::get_config(void) {
    _config_status = read_register(CONFIG_REGISTER);
}

void TMP103::set_high_level(int8_t high_level) {
    //validate input first
    int8_t limit_level = fmax(fmin(MAX_TEMPERATURE, high_level), MIN_TEMPERATURE);
    write_register(THIGH_REGISTER, limit_level);
}

void TMP103::set_low_level(int8_t low_level) {
    //validate input first
    int8_t limit_level = fmax(fmin(MAX_TEMPERATURE, low_level), MIN_TEMPERATURE);
    write_register(TLOW_REGISTER, limit_level);
}

bool TMP103::check_alarms(void) {
    get_config();
    if(_config_status & 0x10){
        //high alarm triggered
        return true;
    }

    if(_config_status & 0x07) {
        //low alarm triggered
        return true;
    }
    return false;
}

void TMP103::enable_alarm_latch(void) { 
    _config_status = (_config_status & 0xFB) | 0x04;
    write_register(CONFIG_REGISTER, _config_status);

} 

void TMP103::disable_alarm_latch(void) {
    _config_status = _config_status & 0xFB;
    write_register(CONFIG_REGISTER, _config_status);

}

void TMP103::set_conversion_rate(int8_t rate) {
    _config_status = (_config_status & 0x9F) | rate;
    write_register(CONFIG_REGISTER, _config_status);

}

void TMP103::shutdown_mode(void) {
    //send config write with last 2 bits = 00
    _config_status = _config_status & 0xFC;
    write_register(CONFIG_REGISTER, _config_status);
}

void TMP103::one_shot_mode(void) {
    //send config write with last 2 bits = 01
    _config_status = _config_status & 0xFD;
    write_register(CONFIG_REGISTER, _config_status);
}

void TMP103::continuous_mode(void) {
    //send config write with last 2 bits = 10
    _config_status = _config_status & 0xFE;
    write_register(CONFIG_REGISTER, _config_status);
}