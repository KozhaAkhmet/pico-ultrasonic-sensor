
#include <stdio.h>
#include <stdlib.h>

#include "hardware/uart.h"
#include "pico/stdlib.h"
#include "ultrasonicObject.h"

uint trigPin = 21;
uint echoPin = 20;

float max(float a, float b) {
    return a > b ? a : b;
}

float min(float a, float b) {
    return a > b ? b : a;
}
// medain filtering algorithm
#define NUM_READ 10
typedef struct {
    float buffer[NUM_READ];  // static buffer
    size_t count;            // counter
} median_param;

median_param median_param_options[] = {
    median_param{.count = 0},
    median_param{.count = 0},
    median_param{.count = 0},
    median_param{.count = 0}};

float median(float newVal, int param) {
    // static float buffer[NUM_READ];  // static buffer
    // static size_t count = 0;        // counter
    median_param_options[param].buffer[median_param_options[param].count] = newVal;
    if (++(median_param_options[param].count) >= NUM_READ) median_param_options[param].count = 0;  // перемотка буфера

    float buf[NUM_READ];  // buffer for median
    for (int i = 0; i < NUM_READ; i++) buf[i] = median_param_options[param].buffer[i];

    for (int i = 0; i <= (int)((NUM_READ / 2) + 1); i++) {  // Sorting with the Buble sort.
        for (int m = 0; m < NUM_READ - i - 1; m++) {
            if (buf[m] > buf[m + 1]) {
                float buff = buf[m];
                buf[m] = buf[m + 1];
                buf[m + 1] = buff;
            }
        }
    }

    float ans = 0;
    if (NUM_READ % 2 == 0) {
        ans = buf[(NUM_READ / 2)];  // picking value in the center
    } else {
        ans = (buf[(NUM_READ / 2)] + buf[((NUM_READ / 2)) + 1]) / 2;  // picking an avarage from two middle values
    }
    return ans;
}

float k = 0.01;  // коэффициент фильтрации, 0.0-1.0

// бегущее среднее
float expRunningAverage(float newVal) {
  static float filVal = 0;
  filVal += (newVal - filVal) * k;
  return filVal;
}

int main() {
    stdio_init_all();
    Ultrasonic ultrasonic(trigPin, echoPin);
    printf("initializing...");
    float raw_value = 0;
    int raw_value_int = 0;
    float raw_median_value = 0;
    float median_twice = 0;
    while (true) {
        raw_value = ultrasonic.getCM<float>();
        raw_value_int = ultrasonic.getCM<int>();
        raw_median_value = median(raw_value, 0);
        median_twice = median(raw_median_value, 2);
        printf("\n%f %f %f %f %f %f",
               raw_value,
               raw_median_value,
               expRunningAverage(raw_value),
               median(expRunningAverage(raw_value), 1),
               median_twice,
               expRunningAverage(median_twice)
               );
        sleep_ms(50);
    }
}
