//This example uses the ultrasonic script to get centimeters and writes it to UART

#include "pico/stdlib.h"
#include <stdio.h>
#include "ultrasonicObject.h"
#include "hardware/uart.h"

int trigPin = 21;
int echoPin = 20;

Ultrasonic myUltrasonic(trigPin, echoPin);

int main()
{
    stdio_init_all();
    while (true) { 
        printf("\n %d cm  %f cm", myUltrasonic.getCM<int>(), myUltrasonic.getCM<float>()); 
        sleep_ms(100);
    }
}