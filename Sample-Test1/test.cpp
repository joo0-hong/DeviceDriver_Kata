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

class DDTestFixture : public testing::Test {
public:
	FlashMock mk;
	DeviceDriver driver = DeviceDriver(&mk);

	const int DEFAULT_ADDR = 0x10;
	const int READ_TRY_COUNT = 5;
};

TEST_F(DDTestFixture, Read5Times) {
	EXPECT_CALL(mk, read)
		.Times(READ_TRY_COUNT);

	driver.read(DEFAULT_ADDR);
}

TEST_F(DDTestFixture, ReadWithException) {
	EXPECT_CALL(mk, read)
		.WillOnce(Return(0x0))
		.WillRepeatedly(Return(0xFF));

	EXPECT_THROW({
		driver.read(DEFAULT_ADDR);
		}, readFailException);
}

TEST_F(DDTestFixture, WriteTest) {
	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0xFA));

	EXPECT_THROW({
		driver.write(DEFAULT_ADDR, 1);
		}, WriteFailException);
}

TEST_F(DDTestFixture, WriteAfterRead) {
	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0xFF));

	driver.write(DEFAULT_ADDR, 1);

	EXPECT_CALL(mk, read)
		.WillRepeatedly(Return(0x1));

	EXPECT_EQ(1, driver.read(DEFAULT_ADDR));
}
