#include "gtest/gtest.h"

#include "shovester/core/component/IO.h"
#include "shovester/core/System.h"
#include "shovester/core/Entity.h"
#include "shovester/core/PointerInput.h"

#include <SDL2/SDL.h>

TEST(testPointerInput, basic) {
    SDLBase sdlbase;

    Window window(
        "ComponentIO.basic",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    Renderer renderer(window.get());

    Entity e({
        new IO<int>("tap", 0),
        new IO<int>("hold", 0),
        new IO<int>("flick", 0)
    });

    auto tap = dynamic_cast<IO<int>*>(e.getComponent("tap"));
    auto hold = dynamic_cast<IO<int>*>(e.getComponent("hold"));
    auto flick = dynamic_cast<IO<int>*>(e.getComponent("flick"));

    auto update = [&rdata]() {
        if (tap->wasUpdated()) {
            std::cout << "tapped." << std::endl;
        }
        if (hold->wasUpdated()) {
            std::cout << "holded." << std::endl;
        }
        if (flick->wasUpdated()) {
            std::cout << "flicked." << std::endl;
        }
    };

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                auto val = rdata->getData();
                if (val < 10) {
                    rdata->setData(rdata->getData() + 1);
                } else {
                    running = false;
                    break;
                }
            }
        }
        update();
    }

}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


