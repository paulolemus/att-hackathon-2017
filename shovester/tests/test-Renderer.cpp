#include "gtest/gtest.h"

#include <shovester/core/SDLBase.h>
#include <shovester/core/Window.h>
#include <shovester/core/Renderer.h>

TEST(Renderer, basic) {
    // Assert that SDL_Init >= 0
    ASSERT_GE(SDL_Init(SDL_INIT_EVERYTHING), 0);

    // Window variable
    SDL_Window* window = NULL;

    // Assert that the SDL_Window is created.
    ASSERT_TRUE(
        NULL !=
        (window = SDL_CreateWindow(
            "Renderer.basic",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1280,
            720,
            SDL_WINDOW_OPENGL
        ))
    );

    // Create the Renderer.
    Renderer renderer(window);

    // Assert that the actual SDL_Renderer* is not NULL
    ASSERT_TRUE(NULL != renderer.get());

    // Breakdown.
    SDL_Quit();
}

/// @brief Tests integration with the Shovester abstraction
///        classes over SDL.
TEST(Renderer, shovesterSystemIntegration) {
    // If this doesn't throw an exception, this is okay.
    SDLBase sdlBase; 

    // Create the window -- throws on error.
    Window window(
        "Renderer.shovesterSystemIntegration",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    // Create the renderer -- if it doesn't throw, this is
    // okay.
    Renderer renderer(window.get());

    // Destruction is handled automatically by destructors.
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


