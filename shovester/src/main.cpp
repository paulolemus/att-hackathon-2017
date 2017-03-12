#include <iostream>
#include <vector>
#include <string>

#include "shovester/core/System.h"
#include "shovester/core/Entity.h"  
#include "shovester/core/TexturePool.h"  
#include "shovester/core/MixChunkPool.h"  
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
    TexturePool texturePool(renderer.get(), "./resources/image/");

    //////////////////////////////////////////////////
    // Loading required textures.
    //////////////////////////////////////////////////
    texturePool.loadResource("ghost_sheet.png", "enemyGhost");
    texturePool.loadResource("player.png", "player");
    texturePool.loadResource("bg.png", "background");
    //////////////////////////////////////////////////
    // Getting vectors of animation frame specs.
    //////////////////////////////////////////////////
    
    //////////////////////////////////////////////////
    // Defining Entity Sprite components with the
    // given information of Textures and rectangles.
    //////////////////////////////////////////////////



    MixChunkPool soundEffectPool("./resources/sound/");
    //////////////////////////////////////////////////
    // NEED TO LOAD SOUND EFFECTS HERE
    //////////////////////////////////////////////////
    soundEffectPool.load_resource("damage1.wav", "damage1");
    soundEffectPool.load_resource("damage2.wav", "damage2");
    soundEffectPool.load_resource("damage3.wav", "damage3");
    soundEffectPool.load_resource("game_over.wav", "gameOver");
    soundEffectPool.load_resource("respawn.wav", "respawn");

    
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Creating entities.
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////
    // Updating function
    //////////////////////////////////////////////////
    auto update = [&]() {};


    //////////////////////////////////////////////////
    // Rendering function
    //////////////////////////////////////////////////
    auto render = [&]() {
    
    };

    //////////////////////////////////////////////////
    // Begin the music.
    //////////////////////////////////////////////////
    Mix_Music* bgMusic = Mix_LoadMUS("./resources/sound/732646_Flower-Math.mp3");
    if (bgMusic == nullptr) {
        throw std::runtime_error(Mix_GetError());
    }
    Mix_FadeInMusic(bgMusic, -1, 10000);

    //////////////////////////////////////////////////
    // Main loop.
    //////////////////////////////////////////////////
    bool done = false;
    while (!done) {

    }

    Mix_FadeOutMusic(10000);
    //////////////////////////////////////////////////
    // Destruction and release of resources happens
    // here automatically.
    //////////////////////////////////////////////////
}
