#ifndef SHOVESTER_CORE_RENDERER_H
#define SHOVESTER_CORE_RENDERER_H

#include <stdexcept>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>

class Renderer {
public:
  Renderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_TARGETTEXTURE |
                                  SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
      std::cerr << "Renderer creation error.\n";
      throw std::runtime_error(SDL_GetError());
    } 
  }

  Renderer(const Renderer& other) = delete;
  Renderer& operator=(const Renderer& other) = delete;

  Renderer(Renderer&& other) {
    this->renderer = other.renderer;
    other.renderer = nullptr;
  }

  Renderer& operator=(Renderer&& other) noexcept {
    this->renderer = other.renderer;
    other.renderer = nullptr;
    return *this;
  }

  ~Renderer() {
    SDL_DestroyRenderer(renderer);
  }

  SDL_Renderer* get() {
    return renderer;
  }

  SDL_Renderer* renderer;
};


#endif // SHOVESTER_CORE_RENDERER_H
