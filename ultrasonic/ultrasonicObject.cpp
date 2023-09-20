#include "ultrasonicObject.h"
extern "C" {
#include "ultrasonic.h"
}
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

Ultrasonic::Ultrasonic(int trigPinToSet, int echoPinToSet)
{
    trigPin = trigPinToSet;
    echoPin = echoPinToSet;
    setupUltrasonicPins(trigPin, echoPin);
}

float Ultrasonic::getPulse()
{
    gpio_put(trigPin, 1);
    sleep_us(10);
    gpio_put(trigPin, 0);

    float width = 0;

    while (gpio_get(echoPin) == 0) tight_loop_contents();
    absolute_time_t startTime = get_absolute_time();
    while (gpio_get(echoPin) == 1) 
    {
        width++;
        sleep_us(1);
        if (width > timeout) return 0;
    }
    absolute_time_t endTime = get_absolute_time();
    
    return absolute_time_diff_us(startTime, endTime);
}

template<>
float Ultrasonic::getCM()
{
    return getCm_float(trigPin, echoPin);
}

template<>
int Ultrasonic::getCM()
{
    return getCm_int(trigPin, echoPin);
}

template<>
float Ultrasonic::getINCH()
{
    return getInch_float(trigPin, echoPin);
}

template<>
int Ultrasonic::getINCH()
{
    return getInch_int(trigPin, echoPin);
}

// T Ultrasonic::getCM()
// {
//     return getCm_(T)(trigPin, echoPin);
// }

// T Ultrasonic::getINCH()
// {
//     return getInch_(T)(trigPin, echoPin);
// }