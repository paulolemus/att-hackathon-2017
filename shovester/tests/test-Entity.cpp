#include "gtest/gtest.h"

#include "shovester/core/Component.h"
#include "shovester/core/component/StringTable.h"
#include "shovester/core/Entity.h"

TEST(Entity, basic) {
    Entity e({
        new StringTable("table")
    });

}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


