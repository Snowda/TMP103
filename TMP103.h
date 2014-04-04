#ifndef AB1850_h
#define AB1850_h
#include <Arduino.h>
#include <wire.h>
#include "stdint.h"

#define TMP103A                 0xF0 //1110000
#define TMP103B                 0xF1 //1110001
#define TMP103C                 0xF2 //1110010
#define TMP103D                 0xF3 //1110011
#define TMP103E                 0xF4 //1110100
#define TMP103F                 0xF5 //1110101
#define TMP103G                 0xF6 //1110110
#define TMP103H                 0xF7 //1110111

#define TEMPERATURE_REGISTER    0x00
#define HIGH_SPEED_COMMAND      0x07 //00001xxx

class TMP103 {
    public:
        TMP103();
        void set_address(uint8_t chip_address);
        uint8_t get_address(void);
        uint8_t read_register(uint8_t temp_register);
        uint8_t write_register(uint8_t temp_register, uint8_t data);
        uint8_t get_data(uint8_t temp_register, uint8_t register_mask);
        void get_temperature(void);
        void print_temperature(void);
        void reset(void);
    private:
        uint8_t _address;
        uint8_t _temperature;
};

#endif