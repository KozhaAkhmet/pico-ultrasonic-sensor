#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
void setupUltrasonicPins(int trigPin, int echoPin);
int getCm_int(int trigPin, int echoPin);
int getInch_int(int trigPin, int echoPin);
float getCm_float(int trigPin, int echoPin);
float getInch_float(int trigPin, int echoPin);
#endif