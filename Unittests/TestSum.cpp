#include <gtest/gtest.h>
#include <limits>
#include <iostream>

// Função definida em um outro arquivo
int Sum(int a, int b)
{
	return a + b;
}

TEST(SumTestSuite, TestSum_Simple)
{
	int r = Sum(2, 2);
	EXPECT_EQ(r, 4);
}

TEST(SumTestSuite, TestSum_Zero)
{
	EXPECT_EQ(Sum(0, 0), 0);
	EXPECT_EQ(Sum(0, -0), 0);
}

TEST(SumTestSuite, TestSum_LargeNumbers)
{
	constexpr int maxInt = std::numeric_limits<int>::max();
	constexpr int minInt = std::numeric_limits<int>::min();

	std::cout << "MaxInt: " << maxInt << '\n';
	std::cout << "MinInt: " << minInt << '\n';

	EXPECT_EQ(Sum(maxInt, 1), minInt);
}