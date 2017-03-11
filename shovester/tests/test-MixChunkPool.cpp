#include "gtest/gtest.h"

#include "shovester/core/System.h"
#include "shovester/core/MixChunkPool.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

TEST(MixChunkPool, basic) {
    // Initializes the SDL systems.
    SDLBase sdlBase;

    // Create the TexturePool from the Renderer.
    MixChunkPool mixChunkPool("./resources/sound/");

    // Load in a test image.
    mixChunkPool.loadResource("Evillaugh.ogg", "test1");

    // Get the sound from the pool.
    auto resource = mixChunkPool.getResource("test1");
    ASSERT_TRUE(resource != NULL);

    // Play the sound.
    ASSERT_NE(-1, Mix_PlayChannel(1, resource, 0));

    // Wait until we're done playing the sound.
    while (Mix_Playing(1) != 0) {}

    // Destroy everything -- things go out of scope.
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


