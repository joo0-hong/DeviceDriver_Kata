#pragma once
#include <stdexcept>
#include "FlashMemoryDevice.h"
using namespace std;

class readFailException : public std::exception {
public:
    explicit readFailException(char const* _Message) 
        : exception (_Message) {    }
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};