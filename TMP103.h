#ifndef TMP103_h
#define TMP103_h
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
#define CONFIG_REGISTER         0x01
#define TLOW_REGISTER           0x02
#define THIGH_REGISTER          0x03
#define HIGH_SPEED_COMMAND      0x07 //00001xxx
#define MAX_TEMPERATURE         127
#define MIN_TEMPERATURE         -55 //note that this is a negative value

#define QUARTER_HZ              0x00 //0.25kHz
#define ONE_HZ                  0x20 //1Hz
#define FOUR_HZ                 0x40 //4Hz
#define EIGHT_HZ                0x60 //8Hz

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
        void get_config(void);
        void set_high_level(int8_t high_level);
        void set_low_level(int8_t low_level);
        void check_alarms(void);
        void enable_alarm_latch(void);
        void disable_alarm_latch(void);
        void set_conversion_rate(int8_t rate);
        void shutdown_mode(void);
        void one_shot_mode(void);
        void continuous_mode(void);
    private:
        uint8_t _address;
        int8_t _temperature; //signed
        uint8_t _config_status;
        bool _high_alarm;
        bool _low_alarm;

};

#endif