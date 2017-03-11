#include "gtest/gtest.h"

#include "shovester/core/MixChunkPool.h"
#include "shovester/core/component/SoundEffect.h"
#include "shovester/core/component/IO.h"
#include "shovester/core/System.h"
#include "shovester/core/Entity.h"

#include <SDL2/SDL.h>

TEST(ComponentSoundEffect, basic) {
    SDLBase sdlbase;

    Window window(
        "ComponentIO.basic",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    Renderer renderer(window.get());

    MixChunkPool sfxPool("./resources/sound/");
    sfxPool.loadResource(
        "Electronic_Chime-KevanGC-495939803.ogg",
        "chime"
    );

    Mix_PlayChannel(-1, sfxPool.getResource("chime"), 0);


    Entity e({
        new IO<int>("mouse_left_click", 0),
        new SoundEffect(
            "sfxChime",
            sfxPool.getResource("chime")
        )
    });

    auto rdata = dynamic_cast<IO<int>*>(e.getComponent("mouse_left_click"));

    // Pseudo update function.
    auto update = [&rdata, &e]() {
        if (rdata->wasUpdated()) {
            // Get the value data in the IO component.
            auto val = rdata->getData();
            // If the value is below 10...
            if (val <= 10) {
                // Get the pointer to the SFX component.
                auto sfx = dynamic_cast<SoundEffect*>(
                    e.getComponent("sfxChime"));
                // If we got the right type of Component...
                if (sfx != nullptr) {
                    if (sfx->get() == nullptr) { throw 1; }
                    // Play the sound at 128/128 full volume.
                    sfx->play(-1, 128);
                }
            }
        } 
    };

    bool running = true;
    while (running) {
        // Get events.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Here, we set the value of the IO component.
                auto val = rdata->getData();

                // If we haven't done 10 clicks yet,
                if (val < 10) {
                    // Set the IO component data to 1+.
                    rdata->setData(rdata->getData() + 1);
                } else {
                    // else, terminate.
                    running = false;
                    break;
                }
            }
        }
        // Now, run the pseudo update.
        update();
    }

}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


