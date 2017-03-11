#include "gtest/gtest.h" 

#include "shovester/core/Window.h"

TEST(Window, basic) {
    // If this runs without throwing an exception, it works.
    Window window(
        "basic", 800, 600, SDL_WINDOW_OPENGL
    );
}

TEST(Window, fullscreen720p) {
    // This is 720p, fullscreen
    Window window720p(
        "fullscreen",
        1280,
        720,
        SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL
    );
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


