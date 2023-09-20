
#include <stdio.h>
#include "pico/stdlib.h"
#include "ultrasonicObject.h" 
#include "hardware/uart.h"

uint trigPin = 21;
uint echoPin = 20;

float max(float a, float b){
    return a > b ? a : b;
}

float min(float a, float b){
    return a > b ? b : a;
}
// medain filtering algorithm
#define NUM_READ 10
float median(float newVal) {
  static float buffer[NUM_READ];  // static buffer
  static size_t count = 0;    // counter
  buffer[count] = newVal;
  if (++count >= NUM_READ) count = 0;  // перемотка буфера
  
  float buf[NUM_READ];    // buffer for median
  for (int i = 0; i < NUM_READ; i++) buf[i] = buffer[i];  

  for (int i = 0; i <= (int) ((NUM_READ / 2) + 1); i++) { // Sorting with the Buble sort.
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
    ans = buf[(NUM_READ / 2)];   // picking value in the center
  } else {
    ans = (buf[(NUM_READ / 2)] + buf[((NUM_READ / 2)) + 1]) / 2; // picking an avarage from two middle values
  }
  return ans;
}

int main() {
    stdio_init_all();
    Ultrasonic ultrasonic(trigPin, echoPin);
    printf("initializing...");
    float raw_value = 0;
    int raw_value_int = 0;
    while (true) {
        raw_value = ultrasonic.getCM<float>();
        raw_value_int = ultrasonic.getCM<int>();

        printf("\n%f %f %d", raw_value, median(raw_value), raw_value_int);
        // printf("\n%f",));
        // printf("\n|");
        sleep_ms(50);
    }
}
