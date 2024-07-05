#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) 
    : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    unsigned char firstVal = m_hardware->read(address);
    for (int i = 0; i < 4; i++) {
        if (firstVal != m_hardware->read(address))
        {
            throw readFailException("READ FAIL !");
        }
    }
    return (int)(firstVal);
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}