#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "shovester/core/System.h"
#include "shovester/core/Entity.h"  
#include "shovester/core/TexturePool.h"  
#include "shovester/core/MixChunkPool.h"  
#include "shovester/core/component/IO.h"  
#include "shovester/core/component/GUI.h"  
#include "shovester/core/component/Physics.h"  
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
    vector<SDL_Rect> enemyGhost;
    	enemyGhost.push_back(enemyGhost.x, enemyGhost.y, enemyGhost.w, enemyGhost.h);
    vector<SDL_Rect> player;
    	player.push_back(player.x, player.y, player.w, player.h);

    vector<SDL_Rect> background;
    	background.push_back(background.x, background.y, background.w, background.h);



    //////////////////////////////////////////////////
    // Defining Entity Sprite components with the
    // given information of Textures and rectangles.
    //////////////////////////////////////////////////



    MixChunkPool soundEffectPool("./resources/sound/");
    //////////////////////////////////////////////////
    // NEED TO LOAD SOUND EFFECTS HERE
    //////////////////////////////////////////////////
    soundEffectPool.loadResource("damage1.wav", "damage1");
    soundEffectPool.loadResource("damage2.wav", "damage2");
    soundEffectPool.loadResource("damage3.wav", "damage3");
    soundEffectPool.loadResource("game_over.wav", "gameOver");
    soundEffectPool.loadResource("respawn.wav", "respawn");
    
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// Creating entities.
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

    // WORLD - ALL PHYSICS DONE HERE
    b2World world( b2Vec2(0, 0) );

    // Player setup  COMMENT THIS IF ERRORS
    b2BodyDef bodyDef;
    b2FixtureDef fixDef;
    b2CircleShape circleShape;
    bodyDef.type - b2_dynamicBody;
    bodyDef.position.Set(1280 / 2.0, 720 / 2.0);
    bodyDef.angle = 0;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = 1.5;
    fixDef.shape = &circleShape;
    fixDef.density = 0.9f;
    Physics playerPhys("phys", &world, bodyDef, fixDef);


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
        // Clear the screen
        SDL_RenderClear(renderer.get());
        // Render the background first.
        const SDL_Rect bgRect = {0, 0, 1280, 720};
        SDL_RenderCopy(
            renderer.get(),
            texturePool.getResource("background"),
            &bgRect,
            &bgRect
        );
        
        // Render Player

        // Render enemies
        SDL_RenderPresent(renderer.get());
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
    // The input data structure.
    //////////////////////////////////////////////////

    struct InputData {
        enum class Action : int {
            PUSHDOWN,
            RELEASE
        };
        Action action;
        float x;
        float y;
        float msDelta;
    };


    //////////////////////////////////////////////////
    // Main loop.
    //////////////////////////////////////////////////
    bool done = false;
    // Recording input data.
    InputData inputData;

    //////////////////////////////////////////////////
    // Recording the time between click down and up.
    //////////////////////////////////////////////////
    using clock = std::chrono::high_resolution_clock;
    auto last_time = clock::now();

    while (!done) {
        auto current_time = clock::now();
        SDL_Event event;
        // Getting input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Gathering data.
                inputData.action = InputData::Action::PUSHDOWN;
                inputData.x = event.motion.x; 
                inputData.y = event.motion.y;
                inputData.msDelta =
                    std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();
                last_time = clock::now();


                ////////////////////////////////////////////////////////////
                std::cout << "inputData(PUSHDOWN): ("
                    << inputData.x << ','
                    << inputData.y << ','
                    << inputData.msDelta << ','
                    << static_cast<int>(inputData.action) << ')'
                    << std::endl;
                ////////////////////////////////////////////////////////////

                
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                // Gathering input data into InputData struct.
                inputData.action = InputData::Action::RELEASE;
                inputData.x = event.motion.x; 
                inputData.y = event.motion.y;
                inputData.msDelta =
                    std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();
                last_time = clock::now();

                ////////////////////////////////////////////////////////////
                std::cout << "inputData(RELEASE): ("
                    << inputData.x << ','
                    << inputData.y << ','
                    << inputData.msDelta << ','
                    << static_cast<int>(inputData.action) << ')'
                    << std::endl;
                ////////////////////////////////////////////////////////////
            }
        }
        update();
        render();
    }

    Mix_FadeOutMusic(10000);
    //////////////////////////////////////////////////
    // Destruction and release of resources happens
    // here automatically.
    //////////////////////////////////////////////////
}
