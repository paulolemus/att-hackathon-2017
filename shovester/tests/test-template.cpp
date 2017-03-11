#include "gtest/gtest.h"

TEST(Example, basic) {

    std::cout << "hello world!" << std::endl;

    ASSERT_TRUE(true);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


