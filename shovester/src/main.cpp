#include <iostream>
#include <vector>
#include <string>

#include "shovester/core/System.h"
#include "shovester/core/Entity.h"  
#include "shovester/core/component/IO.h"  
#include "shovester/core/component/GUI.h"  
#include "shovester/core/component/SoundEffect.h"  
#include "shovester/core/component/Sprite.h"  
#include "shovester/core/component/StringTable.h"  

/// @note Need the command line arguments for SDL
int main(int argc, char** argv) {
    // Initialize the program.
    SDLBase sdlbase;
    // Create the window.
    Window window(
        "Shovester!",
        1280,
        720,
        SDL_WINDOW_OPENGL
    );
    // Create the renderer.
    Renderer renderer(window.get());
    SDL_SetRenderDrawBlendMode(
        renderer.get(),
        SDL_BLENDMODE_BLEND
    );
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

}
