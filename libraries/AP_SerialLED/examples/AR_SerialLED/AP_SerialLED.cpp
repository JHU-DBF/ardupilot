#include <AP_HAL/AP_HAL.h>
#include <AP_SerialLED/AP_SerialLED.h>


void setup();
void loop();

const AP_HAL::HAL& hal = AP_HAL::get_HAL();
static AP_SerialLED *led = nullptr;
// static AP_SerialLED *led2 = nullptr;
// static AP_SerialLED *led3 = nullptr;

#define NEOPIXEL_LED_LOW    0x33
#define NEOPIXEL_LED_MEDIUM 0x7F
#define NEOPIXEL_LED_HIGH   0xFF
#define NEOPIXEL_LED_OFF    0x00

unsigned int chan = 12;

void setup()
{
    hal.console->printf("NeoPixel LED test\n");


    // if (led == nullptr) {
    //     hal.console->printf("Failed to initialise NeoPixel LED\n");
    // }
    hal.rcout->init();
    hal.rcout->enable_ch(chan);
    bool result = led->set_num_neopixel(chan, 16);
    if (!result) {
        hal.console->printf("Failed to initialise NeoPixel LED\n");
    }

    led->set_RGB(chan, -1, NEOPIXEL_LED_HIGH, NEOPIXEL_LED_HIGH, NEOPIXEL_LED_HIGH);
    // led->set_RGB(12, -1, 0, 0, 0);
    led->send(chan);
    // led2 = AP_SerialLED::get_singleton();
    // led2->set_num_neopixel(13, 16);
    // led2->set_RGB(13, -1, NEOPIXEL_LED_HIGH, 0, 0);
    // // led2->set_RGB(13, -1, 0, 0, 0);
    // led2->send(13);

    // led3 = AP_SerialLED::get_singleton();
    // led3->set_num_neopixel(11, 16);
    // led3->set_RGB(11, -1, NEOPIXEL_LED_HIGH, 0, 0);
    // // led3->set_RGB(11, -1, 0, 0, 0);
    // led3->send(11);
    // led->set_RGB(12, 1, 0, 255, 0);
    // led->set_RGB(12, 2, 0, 0, 255);
    // led->set_RGB(12, 3, 255, 255, 255);

    // if (ret == 0) {
    //     hal.console->printf("Failed to initialise NeoPixel LED\n");
    // }
}

unsigned int k = 0;

void loop()
{
    for (size_t j = 0; j < 4; j++)
    {
        led->set_RGB(chan, j, 0, k*NEOPIXEL_LED_HIGH, 0);
    }
    for (size_t j = 4; j < 8; j++)
    {
        led->set_RGB(chan, j, k*NEOPIXEL_LED_HIGH, 0, 0);
    }
    for (size_t j = 8; j < 12; j++)
    {
        led->set_RGB(chan, j, 0, 0, k*NEOPIXEL_LED_HIGH);
    }
    for (size_t j = 12; j < 16; j++)
    {
        led->set_RGB(chan, j, k*NEOPIXEL_LED_HIGH, k*NEOPIXEL_LED_HIGH, 0);
    }
    // led->set_RGB(i, j%4, 255, 0, 0);
    // led->set_RGB(i, j%4+1, 0, 255, 0);
    // led->set_RGB(i, j%4+2, 0, 0, 255);
    // led->set_RGB(i, j%4+3, 255, 255, 255);
    // led->set_RGB(12, -1, i%NEOPIXEL_LED_HIGH, NEOPIXEL_LED_HIGH, NEOPIXEL_LED_HIGH);
    // led->send(12);
    // led2->set_RGB(13, -1, NEOPIXEL_LED_HIGH, i%NEOPIXEL_LED_HIGH, NEOPIXEL_LED_HIGH);
    // led2->send(13);
    // led3->set_RGB(11, -1, NEOPIXEL_LED_HIGH, NEOPIXEL_LED_HIGH, i%NEOPIXEL_LED_HIGH);
    // led3->send(11);
    k++;
    if (k == 256)
    {
        k = 0;
    }
    led->send(chan);
    // hal.console->printf("Updated LED\n");

    hal.scheduler->delay(500);
}

AP_HAL_MAIN();
