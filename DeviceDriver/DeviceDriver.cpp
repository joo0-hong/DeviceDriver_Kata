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
	// Read
	int current = read(address);

	if (current == 0xFF)
	{
		// If 0xFF, write
		m_hardware->write(address, (unsigned char)data);
	}
	else
	{
		// If not 0xFF, exception
		throw WriteFailException("Written Address");
	}

}