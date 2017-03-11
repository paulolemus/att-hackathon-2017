#ifndef SHOVESTER_CORE_SDLBASE_H
#define SHOVESTER_CORE_SDLBASE_H

#include <stdexcept>
#include <memory>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class SDLBase {
public:
    SDLBase() {
        // Failed to initialize SDL base.
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            throw std::runtime_error(SDL_GetError());
        }

        //SDL_image subsystem init
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            std::cerr << "Image loading subsystem initialization error.\n";
            throw std::runtime_error(IMG_GetError());
        }

        //SDL_ttf subsystem init
        if (TTF_Init() < 0) {
            std::cerr << "TTF subsystem initialization error.\n";
            throw std::runtime_error(TTF_GetError());
        }

        //SDL_mixer subsystem init
        int mixerFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
        if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags) {
            std::cerr << "Audio mixer subsystem initialization error.\n";
            throw std::runtime_error(Mix_GetError());
        }

        // SDL_Mixer open audio channel.
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
            std::cerr << "Audio mixer open audio failed.\n";
            throw std::runtime_error(Mix_GetError());
        }
    }

    ~SDLBase() {
        IMG_Quit();
        TTF_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
    }
};

#endif // SHOVESTER_CORE_SDL_BASE_H

