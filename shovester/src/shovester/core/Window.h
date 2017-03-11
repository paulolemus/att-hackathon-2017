#ifndef SHOVESTER_CORE_WINDOW_H
#define SHOVESTER_CORE_WINDOW_H

#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <stdio.h>

class Window {
public:
    Window(
        std::string title,
        int         width,
        int         height,
        Uint32      flags   
    ) : title(title),
        width(width),
        height(height),
        flags(flags),
        window(NULL) {
       
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            flags
        );

        // Failed to create a window.
        if (!window) {
            throw std::runtime_error(
                std::string(
                "Window.Window(): Could not create window: "
                ).append(std::string(SDL_GetError()))
            );
        }
    }

    ~Window() {
        // Close and destroy the Window.
        SDL_DestroyWindow(window);
    }
private:
    std::string title;
    int         width;
    int         height;
    Uint32      flags;
    SDL_Window* window;
};

#endif // SHOVESTER_CORE_WINDOW_H

