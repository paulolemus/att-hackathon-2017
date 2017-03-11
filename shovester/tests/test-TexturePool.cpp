#include "gtest/gtest.h"

#include "shovester/core/System.h"
#include "shovester/core/TexturePool.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

TEST(TexturePool, basic) {
    // Initializes the SDL systems.
    SDLBase sdlBase;

    // Create the Window and Renderer.
    Window window("TexturePool.basic", 1280, 720, SDL_WINDOW_OPENGL);
    Renderer renderer(window.get());

    // Create the TexturePool from the Renderer.
    TexturePool texturePool(renderer.get(), "./resources/image/");

    // Load in a test image.
    texturePool.loadResource("Tv-test-pattern-146649_640.png", "test1");

    // Clear screen
    SDL_RenderClear(renderer.get());

    auto resource = texturePool.getResource("test1");
    ASSERT_TRUE(resource != NULL);

    // Render the text image.
    SDL_RenderCopy(
        renderer.get(), 
        texturePool.getResource("test1"),
        NULL,
        NULL
    );

    // Update the screen.
    SDL_RenderPresent(renderer.get());

    // Pause for 1 second.
    SDL_Delay(1000);

    // Unload the image.
    texturePool.unloadResource("test1");

    // Destroy everything -- things go out of scope.
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


