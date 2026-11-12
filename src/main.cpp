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

    esc.write(0.0f); // start output with 0% power

    Serial.println("pless any key to start");
    while (!Serial.available())
    {
    }
    Serial.read(); // flush
    Serial.println("start!");
}

void loop()
{
    esc.write(0.1f);
    delay(1000);
    esc.write(0.0f);
    delay(1000);
}
