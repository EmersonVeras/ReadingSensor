#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <stdio.h>  
#include <string>
#include "sensors.h"

std::string exec(const char* cmd){
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed");
    try{
        while(fgets(buffer, sizeof buffer, pipe) != NULL){
            result += buffer;
        }
    } catch(...){
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

int map(float x, float in_min, float in_max, float out_min, float out_max){
    return (x -in_min)*(out_max - out_min)/(in_max - in_min) + out_min;

}

int temperatureSensor(){
    std::string stringTemperature;
    stringTemperature = exec("sh /home/pi/test/analog/get-analog-input I0.7");
    float inputTemperature = std::stof(stringTemperature);
    //Normalyze data
    float temperature = map(inputTemperature, 0, 2048, -50, 150);
    return temperature;
}

int vibrationSensor(){
    std::string stringVibration;
    stringVibration = exec("sh /home/pi/test/analog/get-analog-input I0.8");
    float inputVibration = std::stof(stringVibration);
    //Normalyze data
    float vibration = map(inputVibration, 0, 2048, 1, 1000);
    return vibration;
}