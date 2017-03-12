#include "gtest/gtest.h"

#include "shovester/core/component/IO.h"
#include "shovester/core/component/GUI.h"
#include "shovester/core/System.h"
#include "shovester/core/Entity.h"
#include "shovester/core/Text.h"

#include <SDL2/SDL.h>

TEST(ComponentGUI, basic) {
    SDLBase sdlbase;

    Window window(
        "ComponentIO.basic",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    Renderer renderer(window.get());

    Font font("./resources/font/DejaVuSansMono.ttf", 12);
    Text scoreText(font, {255,0,0,255});
    scoreText.setText("Score: 0");


    Entity e({
        new IO<int>("mouse_left_click", 0),
        new GUI<Text>("scoreText", scoreText)
    });

    auto rdata = dynamic_cast<IO<int>*>(e.getComponent("mouse_left_click"));

    auto guiDraw = dynamic_cast<GUI<Text>*>(e.getComponent("scoreText"));

    int counter = 0;
    auto update = [&]() {
        if (rdata->wasUpdated()) {
            auto val = rdata->getData();
            if (val <= 10) {
                ++counter;
                std::cout << std::to_string(counter) << std::endl;
                guiDraw->getData().setText(
                    std::string("Score: ") + std::to_string(counter)
                );
                std::cout << "Mouse clicked: " << val << std::endl;
            }

        } 
    };

    auto render = [&]() {
        if (guiDraw) {
            SDL_RenderClear(renderer.get());
            SDL_Rect bounds = {
                720,
                320,
                120,
                50
            };
            guiDraw->draw(renderer.get(), bounds);
            SDL_RenderPresent(renderer.get());
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
        render();
    }

}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


