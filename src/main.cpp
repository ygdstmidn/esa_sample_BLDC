#include <Arduino.h>
#include <BLDC_ESC_SKYWALKER.hpp>

#define ESC_PIN PA_10

BLDC_ESC_SKYWALKER esc(ESC_PIN);

void setup()
{
    Serial.begin(115200);
    Serial.println("esa_sample_BLDC");
    Serial.println(__DATE__);
    Serial.println(__TIME__);

#if (1) // calibration 必要に応じてif(0)とし，この工程をスキップします
    Serial.println("pless any key to start calibration...");
    while (!Serial.available())
    {
    }
    Serial.println("calibration starting...");
    esc.calibration();
    Serial.println("calibration done");
    while (Serial.available())
    {
        Serial.read();
    }
#endif

    esc.write(0.0f); // start output with 0% power
}

void loop()
{
    const uint32_t now = millis();
    static uint32_t pre = now;

    if (now - pre >= 10) // 100Hz
    {
        while (Serial.available())
        {
            const char keyboardInput = Serial.read();
            int power = 0;
            switch (keyboardInput)
            {
                case 'Q':
                    power = 1;
                    break;
                case 'W':
                    power = 2;
                    break;
                case 'E':
                    power = 3;
                    break;
                case 'R':
                    power = 4;
                    break;
                case 'T':
                    power = 5;
                    break;
                case 'Y':
                    power = 6;
                    break;
                case 'U':
                    power = 7;
                    break;
                case 'I':
                    power = 8;
                    break;
                case 'O':
                    power = 9;
                    break;
                case 'P':
                    power = 10;
                    break;
                default:
                    power = 0;
                    break;
            }
            Serial.printf("power=%d%%\n", power);
            esc.write(power / 100.0f); // 1~10[%]
        }

        pre = now;
    }
}
