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
    // Setup the renderer
    SDL_SetRenderDrawBlendMode(
        renderer.get(),
        SDL_BLENDMODE_BLEND
    );
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

    // Create the texture pool.
    TexturePool texturePoool(renderer.get(), "./resources/image/");
    //////////////////////////////////////////////////
    // NEED TO LOAD TEXTURES HERE
    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
    // NEED TO SETUP THE ANIMATION FRAME BOXES HERE
    //////////////////////////////////////////////////



    MixChunkPool soundEffectPool("./resources/sound/")
    //////////////////////////////////////////////////
    // NEED TO LOAD SOUND EFFECTS HERE
    //////////////////////////////////////////////////



    //////////////////////////////////////////////////
    // Updating function
    //////////////////////////////////////////////////
    auto update = [&]() {};


    //////////////////////////////////////////////////
    // Rendering function
    //////////////////////////////////////////////////
    auto render = [&]() {};

    //////////////////////////////////////////////////
    // Main loop.
    //////////////////////////////////////////////////

    bool done = false;
    while (!done) {

    }

    //////////////////////////////////////////////////
    // Destruction and release of resources happens
    // here automatically.
    //////////////////////////////////////////////////
}
