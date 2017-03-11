#include "gtest/gtest.h"
#include "sol.hpp"

TEST(Lua, cppToLua) {

//    std::cout << "hello world!" << std::endl;

//    ASSERT_TRUE(true);
	
	sol::state lua;
	int value = 21;

	//sol::load_result script = lua.script("value");

	//ASSERT_EQ(script, 21);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


