#include "gtest/gtest.h"

#include <chrono>

#include "shovester/core/component/IO.h"
#include "shovester/core/component/Sprite.h"
#include "shovester/core/System.h"
#include "shovester/core/Entity.h"
#include "shovester/core/TexturePool.h"

#include <SDL2/SDL.h>

TEST(ComponentSprite, basic) {
    SDLBase sdlbase;

    Window window(
        "ComponentIO.basic",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    Renderer renderer(window.get());
    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

    TexturePool texturePool(renderer.get(), "./resources/image/");
    texturePool.loadResource("lazyfoo_animation.png", "sprite");
    
    std::vector<SDL_Rect> boxes;
    for (auto i = 0; i < 3; ++i) {
        SDL_Rect r = {
            i*64,
            0,
            64,
            205
        };
        boxes.push_back(r);
    }

    Entity e({
        new IO<int>("mouse_left_click", 0),
        new Sprite("sprite_sheet", texturePool.getResource("sprite"), boxes)
    });

    auto spriteData = dynamic_cast<Sprite*>(e.getComponent("sprite_sheet"));
    ASSERT_TRUE(spriteData != nullptr);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = t2 - t1;
    auto update = [&]() {
        t1 = t2;
        t2 = std::chrono::high_resolution_clock::now();
        delta += t2 - t1;

        if (delta.count() > 1.0/15.0) {
            std::cout << delta.count() << " s" << std::endl;
            spriteData->nextFrame();          
            delta = std::chrono::duration<double>::zero();
        }
    };


    SDL_Rect dstrect = {640-32, 360-100, 64, 205};
    auto render = [&]() {
        SDL_RenderClear(renderer.get());
        SDL_RenderCopyEx(
            renderer.get(),
            spriteData->getTexture(),
            &spriteData->getRect(),
            &dstrect,
            spriteData->getRotation(),
            NULL,
            SDL_FLIP_NONE
        );
        SDL_RenderPresent(renderer.get());
    };

    auto rdata = dynamic_cast<IO<int>*>(e.getComponent("mouse_left_click"));
    ASSERT_TRUE(rdata != nullptr);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                auto val = rdata->getData();
                rdata->setData(rdata->getData() + 1);
            }
        }
        if (rdata->getData() > 0 ) { running = false; break; }
        update();
        render();
    }

}

TEST(ComponentSprite, rotation) {
    SDLBase sdlbase;

    Window window(
        "ComponentIO.basic",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );

    Renderer renderer(window.get());
    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

    TexturePool texturePool(renderer.get(), "./resources/image/");
    texturePool.loadResource("lazyfoo_animation.png", "sprite");
    
    std::vector<SDL_Rect> boxes;
    for (auto i = 0; i < 3; ++i) {
        SDL_Rect r = {
            i*64,
            0,
            64,
            205
        };
        boxes.push_back(r);
    }

    Entity e({
        new IO<int>("mouse_left_click", 0),
        new Sprite("sprite_sheet", texturePool.getResource("sprite"), boxes)
    });

    auto spriteData = dynamic_cast<Sprite*>(e.getComponent("sprite_sheet"));
    ASSERT_TRUE(spriteData != nullptr);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> delta = t2 - t1;
    auto update = [&]() {
        t1 = t2;
        t2 = std::chrono::high_resolution_clock::now();
        delta += t2 - t1;

        if (delta.count() > 1.0/15.0) {
            std::cout << delta.count() << " s" << std::endl;
            spriteData->nextFrame();
            spriteData->setRotation(
                spriteData->getRotation() + 20.0 
            );
            delta = std::chrono::duration<double>::zero();
        }
    };


    SDL_Rect dstrect = {640-32, 360-100, 64, 205};
    auto render = [&]() {
        SDL_RenderClear(renderer.get());
        SDL_RenderCopyEx(
            renderer.get(),
            spriteData->getTexture(),
            &spriteData->getRect(),
            &dstrect,
            spriteData->getRotation(),
            NULL,
            SDL_FLIP_NONE
        );
        SDL_RenderPresent(renderer.get());
    };

    auto rdata = dynamic_cast<IO<int>*>(e.getComponent("mouse_left_click"));
    ASSERT_TRUE(rdata != nullptr);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                auto val = rdata->getData();
                rdata->setData(rdata->getData() + 1);
            }
        }
        if (rdata->getData() > 0 ) { running = false; break; }
        update();
        render();
    }

}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}


