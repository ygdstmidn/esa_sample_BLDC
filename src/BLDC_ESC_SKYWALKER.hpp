#ifndef __BLDC_ESC_HPP__
#define __BLDC_ESC_HPP__

#include <Arduino.h>

class BLDC_ESC_SKYWALKER
{
   public:
    BLDC_ESC_SKYWALKER(const PinName pin);
    void init();
    void write(const float value) const;

   private:
    constexpr static uint32_t ESC_FREQUENCY = 50;
    constexpr static uint32_t ESC_MIN = (65535 / 20); // 50hz(20ms),1ms
    constexpr static uint32_t ESC_MAX = (65535 / 10); // 50hz(20ms),2ms
    PinName _pin;
    bool _setupDone = false;
};

BLDC_ESC_SKYWALKER::BLDC_ESC_SKYWALKER(PinName pin) : _pin(pin)
{
}

/// @attention 6000ms delay!! ピッ．．．ピッ．．．のタイミングで使用すること！！
void BLDC_ESC_SKYWALKER::init()
{
    if (_pin == NC)
    {
        Serial.println("BLDC_ESC_SKYWALKER: pin is not connected");
        return;
    }
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    pwm_start(_pin, ESC_FREQUENCY, ESC_MAX, RESOLUTION_16B_COMPARE_FORMAT);
    delay(3000);
    pwm_start(_pin, ESC_FREQUENCY, ESC_MIN, RESOLUTION_16B_COMPARE_FORMAT);
    delay(3000);
    _setupDone = true;
}

/// value:0~1
void BLDC_ESC_SKYWALKER::write(const float value) const
{
    if (_setupDone == false)
    {
        Serial.println("BLDC_ESC_SKYWALKER: not initialized");
        return;
    }
    float value_ = value; // make copy
    if (isnan(value))
    {
        return;
    }
    if (value_ > 1.0f)
    {
        value_ = 1.0f;
    }
    else if (value_ < 0.0f)
    {
        value_ = 0.0f;
    }
    int pwmValue = (ESC_MAX - ESC_MIN) * value_ + ESC_MIN;
    pwm_start(_pin, ESC_FREQUENCY, pwmValue, RESOLUTION_16B_COMPARE_FORMAT);
}

#endif // __BLDC_ESC_HPP__
