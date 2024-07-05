#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
using namespace std;
using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	FlashMock() {}
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, Read5Times) {
	//arrange 
	FlashMock mk;
	DeviceDriver driver = DeviceDriver(&mk);

	EXPECT_CALL(mk, read)
		.Times(5)	                      // Behavior Verification
		.WillRepeatedly(Return(10000));   // Stub

	//act
	try {
		driver.read(10);
	}
	catch (readFailException e) {
		cout << e.what() << endl;
	}
}

TEST(TestCaseName, WriteTest) {
	//arrange 
	FlashMock mk;
	DeviceDriver driver = DeviceDriver(&mk);

	EXPECT_CALL(mk, read)
		.Times(AtLeast(5))	                      // Behavior Verification
		.WillRepeatedly(Return(0xFF));   // Stub

	//act
	try {
		driver.write(10, 1);
	}
	catch (WriteFailException e) {
		cout << e.what() << endl;
	}
}