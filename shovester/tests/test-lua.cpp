#include "gtest/gtest.h"
#include "sol.hpp"
#include <string>
#include <vector>
#include "../src/shovester/core/component/IO.h"
#include "../src/shovester/core/System.h"

int factorial(int num) {
	if(num > 1) {
		num *= factorial(num-1);
	}

	else return 1;
}

TEST(Lua, LuaToCpp) {
	sol::state lua;
	int value = lua.script ("return 21");

	ASSERT_EQ(value, 21);
}

TEST(Lua, CppToLua) {
	sol::state lua;
	int value = 21;

	lua["luaVal"] = value;
	auto luaVal = lua.get<int>("luaVal");
	ASSERT_EQ(luaVal, 21);
}

TEST(Lua, CppFactorial) {
	sol::state lua;
	lua["f"] = factorial;

	int f = lua["f"](4);
	ASSERT_EQ(f, 24);
}

TEST(Lua, LuaFactorial) {
	sol::state lua;	
	lua.script_file("./src/shovester/core/lua/factorial.lua");
	sol::function fn = lua["factorial"];
	int f = fn(4);

	ASSERT_EQ(f, 24);
}

TEST(Lua, HealthDamage) {
	sol::state lua;
	int health = 100;
	int damage = 20;

	lua.script_file("./src/shovester/core/lua/script.lua");
	sol::function dmg = lua["Damage"];
	health = dmg(health, damage);

	ASSERT_EQ(health, 80);
}

TEST(Lua, Component) {
	sol::state lua;
	IO<int> *io = new IO<int>("leftMouseClick", 1);
	lua.script_file("./src/shovester/core/lua/script.lua");
	sol::function comp = lua["Component"];

	sol::table component = lua["component"];
	sol::table isIO = component["isIO"];
	isIO["name"] = io->getName();
	isIO["data"] = io->getData();

	std::string c = comp(component);
	
	ASSERT_EQ(c, "IO");
}

TEST(Lua, Frames) {
	int count = 0;
	sol::state lua;
	lua.script_file("./src/shovester/core/lua/frame.lua");
	sol::function frame = lua["frameBoxes"];

	
	std::vector<SDL_Rect> rect; 
	rect.push_back({0,0,0,0});
	rect[count] = frame(1,1,1,1);
	count++;

//	ASSERT_EQ(rect[0].x, 1);

	rect.push_back({0,0,0,0});
	rect[count] = frame(2,2,2,2);
	count++;
	ASSERT_EQ(rect[1].x, 2);
//	ASSERT_EQ(rect[1].x, 2);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


