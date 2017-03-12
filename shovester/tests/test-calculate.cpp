#include "gtest/gtest.h"
#include "../src/shovester/calculateAngleToOther.h"

TEST(Calcualtor, basic) {

    double c = calculateAngleToOther(30, 20, 70, 40);

    ASSERT_EQ(c, 26.57);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


