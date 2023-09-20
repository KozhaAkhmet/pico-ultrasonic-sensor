#ifndef _ULTRASONICOBJECT_H_
#define _ULTRASONICOBJECT_H_
class Ultrasonic
{
    private:
    int trigPin;
    int echoPin;
    int timeout = 26100;

    public:
    Ultrasonic(int trigPin, int echoPin);
    float getPulse();
    template <typename T>
    T getCM();
    template <typename T>
    T getINCH();
};
#endif