#include "gtest/gtest.h"

#include "shovester/core/Component.h"
#include "shovester/core/component/StringTable.h"
#include "shovester/core/Entity.h"

TEST(Entity, basicUsage) {
    Entity e({
        new StringTable("table")
    });

    ASSERT_TRUE(e.getComponent("table") != NULL);

    // Get the StringTable*, and use it..
    auto ptr = e.getComponent("table");
    if (auto table = dynamic_cast<StringTable*>(ptr)) {
        table->set("number1", "1");

        auto num_str = table->get("number1");

        ASSERT_EQ(std::stoi(num_str), 1);
    } else {
        FAIL() << "could not get a StringTable";
    }
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


