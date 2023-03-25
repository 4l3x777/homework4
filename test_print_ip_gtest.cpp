#include "gtest/gtest.h"
#include "print_ip.h"
#include <iostream>
#include <list>

using namespace std;

class TestPrintIp : public ::testing::Test 
{
	streambuf* old_stdout{nullptr};

protected:
	void SetUp() 
	{
		old_stdout = std::cout.rdbuf(new_stdout.rdbuf());
	}

	void TearDown() 
	{
		old_stdout = std::cout.rdbuf(old_stdout);
	}

	stringstream new_stdout;
};

TEST_F(TestPrintIp, test_int8_t)
{
	print_ip( int8_t{-1} ); // 255
	ASSERT_EQ(new_stdout.str(), string("255\n"));
}

TEST_F(TestPrintIp, test_int16_t)
{
	print_ip( int16_t{0} ); // 0.0
	ASSERT_EQ(new_stdout.str(), string("0.0\n"));
}

TEST_F(TestPrintIp, test_int32_t)
{
	print_ip( int32_t{2130706433} ); // 127.0.0.1
	ASSERT_EQ(new_stdout.str(), string("127.0.0.1\n"));
}

TEST_F(TestPrintIp, test_int64_t)
{
	print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
	ASSERT_EQ(new_stdout.str(), "123.45.67.89.101.112.131.41\n");
}

TEST_F(TestPrintIp, test_string)
{
	print_ip( std::string{"Hello, World!"} ); // Hello, World!
	ASSERT_EQ(new_stdout.str(), "Hello, World!\n");
}

TEST_F(TestPrintIp, test_vector)
{
	print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
	ASSERT_EQ(new_stdout.str(), "100.200.300.400\n");
}

TEST_F(TestPrintIp, test_list)
{
	print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
	ASSERT_EQ(new_stdout.str(), "400.300.200.100\n");
}

TEST_F(TestPrintIp, test_tuple)
{
	print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
	ASSERT_EQ(new_stdout.str(), "123.456.789.0\n");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}