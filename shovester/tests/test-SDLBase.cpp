#include "gtest/gtest.h"

#include <shovester/core/SDLBase.h>

TEST(SDLBase, initiaization) {

    SDLBase sdlBase();     

    ASSERT_TRUE(true);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


