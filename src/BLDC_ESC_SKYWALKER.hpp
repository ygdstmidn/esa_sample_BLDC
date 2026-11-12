#ifndef __BLDC_ESC_SKYWALKER_HPP__
#define __BLDC_ESC_SKYWALKER_HPP__

#include <Arduino.h>

class BLDC_ESC_SKYWALKER
{
   public:
    BLDC_ESC_SKYWALKER(const PinName pin);
    void calibration() const;
    void write(float value) const;

   private:
    static constexpr uint32_t ESC_FREQUENCY = 50;
    static constexpr uint32_t ESC_MIN = (65535 / 20); // 50hz(20ms),1ms
    static constexpr uint32_t ESC_MAX = (65535 / 10); // 50hz(20ms),2ms
    const PinName _pin;
};

BLDC_ESC_SKYWALKER::BLDC_ESC_SKYWALKER(PinName pin) : _pin(pin)
{
}

/// @attention 5200ms delay!! ピッ．．．ピッ．．．のタイミングで使用すること！！
void BLDC_ESC_SKYWALKER::calibration() const
{
    write(1.0f);
    delay(1500);
    write(0.0f);
    delay(4700);
}

/// value:0~1
void BLDC_ESC_SKYWALKER::write(float value) const
{
    if (_pin == NC)
    {
        return;
    }

    if (isnan(value))
    {
        return;
    }
    if (value > 1.0f)
    {
        value = 1.0f;
    }
    else if (value < 0.0f)
    {
        value = 0.0f;
    }
    int pwmValue = (ESC_MAX - ESC_MIN) * value + ESC_MIN;
    pwm_start(_pin, ESC_FREQUENCY, pwmValue, RESOLUTION_16B_COMPARE_FORMAT);
}

#endif // __BLDC_ESC_SKYWALKER_HPP__
