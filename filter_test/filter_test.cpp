// This example uses the ultrasonic script to get centimeters and writes it to UART

#include <stdio.h>

#include "pico/stdlib.h"
extern "C" {
#include "ultrasonic.h"
}
#include "hardware/uart.h"

uint trigPin = 2;
uint echoPin = 3;

typedef int byte;

float max(float a, float b){
    return a > b ? a : b;
}

float min(float a, float b){
    return a > b ? b : a;
}
// медиана на 3 значения со своим буфером
#define NUM_READ 3
float median(float newVal) {
  static float buffer[NUM_READ];  // статический буфер
  size_t count = 0;    // счётчик
  buffer[count] = newVal;
  if (++count >= NUM_READ) count = 0;  // перемотка буфера
  
  float buf[NUM_READ];    // локальный буфер для медианы
  for (byte i = 0; i < NUM_READ; i++) buf[i] = buffer[i];  
  for (int i = 0; i <= (int) ((NUM_READ / 2) + 1); i++) { // пузырьковая сортировка массива (можно использовать любую)
    for (int m = 0; m < NUM_READ - i - 1; m++) {
      if (buf[m] > buf[m + 1]) {
        float buff = buf[m];
        buf[m] = buf[m + 1];
        buf[m + 1] = buff;
      }
    }
  }
  float ans = 0;
  if (NUM_READ % 2 == 0) {             // кол-во элементов в массиве четное (NUM_READ - последний индекс массива)
    ans = buf[(NUM_READ / 2)];   // берем центральное
  } else {
    ans = (buf[(NUM_READ / 2)] + buf[((NUM_READ / 2)) + 1]) / 2; // берем среднее от двух центральных
  }
  return ans;
}

int main() {
    stdio_init_all();
    setupUltrasonicPins(trigPin, echoPin);
    printf("initializing...");
    float value = 0;
    while (true) {
        value = getCm(trigPin, echoPin);
        printf("%f\n", median(value));
        sleep_ms(100);
    }
}

// int main() {
//     stdio_init_all();
//     setupUltrasonicPins(trigPin, echoPin);
//     printf("initializing...");
//     float value = 0;
//     while (true) {
        
//         printf("\n %f cm", getCm(trigPin, echoPin));
//         sleep_ms(100);
//     }
// }