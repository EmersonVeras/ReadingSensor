#include <iostream>
#include "sensors.h"

int main(){

    std::cout << temperatureSensor() << "\n";
    std::cout << vibrationSensor() << "\n";    
    return 0;
}