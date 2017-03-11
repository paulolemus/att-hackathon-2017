#include "gtest/gtest.h"

#include "shovester/core/component/IO.h"
#include "shovester/core/System.h"
#include "shovester/core/Entity.h"

#include <SDL2/SDL.h>

TEST(ComponentIO, basic) {
    SDLBase sdlbase;

    Window window(
        "ComponentIO.basic",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    Renderer renderer(window.get());

    Entity e({
        new IO<int>("mouse_left_click", 0)
    });

    auto rdata = dynamic_cast<IO<int>*>(e.getComponent("mouse_left_click"));

    auto update = [&rdata]() {
        if (rdata->wasUpdated()) {
            auto val = rdata->getData();
            if (val <= 10) {
                std::cout << "Mouse clicked: " << val << std::endl;
            }
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


