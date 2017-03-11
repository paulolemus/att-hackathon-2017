#ifndef SHOVESTER_CORE_TEXTUREPOOL_H
#define SHOVESTER_CORE_TEXTUREPOOL_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "shovester/core/IResourcePool.h"
#include "shovester/core/Renderer.h"

/// @brief Holds SDL_Texture*, and loads it from
///        files, prefixed by the path.
template <typename ResourceType = SDL_Texture*>
class TexturePool : public IResourcePool<ResourceType> {
public:
    /// @brief Must take a Renderer to load the image and turn it
    ///        into a SDL_Texture*. Also must take a path string to
    ///        find alternatives.
    TexturePool(SDL_Renderer* renderer, std::string path) :
        path(path),
        renderer(renderer) {}

    /// @brief Frees the textures in the map.
    ~TexturePool() {
        for (auto it : pool) {
            SDL_DestroyTexture(it.second);
        }
    }

    virtual void loadResource (std::string key, std::string label = "") override {
        SDL_Surface* surface = NULL;
        SDL_Texture* texture = NULL;

        // If you cannot load a file with that key name from the
        // current execution environment, instead, look for it in
        // the path.
        if ((surface = IMG_Load(key.c_str())) == NULL) {
            surface = IMG_Load((path + key).c_str());
        }

        // If the surface could not be loaded, throw an error.
        if (surface == NULL) {
            std::string str("Could not load texture file: ");
            str += path;
            str += key;
            throw std::runtime_error(str.c_str());

        // Otherwise, create an SDL_Texture* from the SDL_Surface*
        // using the SDL texture.
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            // If there is no texture, then throw an error.
            if (texture == NULL) {
                std::string str("Could not convert surface to texture: ");
                str += key;
                throw std::runtime_error(str.c_str());

            // Otherwise, setup the texture in the unordered map.
            } else {
                // If the label is nothing, just use the key as the label
                if (label == "") {
                    label = key;
                }
                if (pool.find(label) == pool.end()) {
                    pool[label] = texture;
                } else {
                    std::string str("Cannot insert onto existing key: ");
                    str += key;
                    throw std::runtime_error(str.c_str());
                }
            }
        }
    }

    /// @brief Unloads the resource only if it is there.
    virtual void unloadResource (std::string label) override {
        // Only unload the resource if it matches the key.
        auto element = pool.find(label);
        if (element != pool.end()) {
            pool.erase(element);
        }
    }

    /// @brief Returns NULL if it cannot find the SDL_Texture*
    virtual ResourceType getResource (std::string label) override {
        auto element = pool.find(label);
        if (element != pool.end()) {
            return element->second;
        } else {
            return NULL;
        }
    }

private:
    std::unordered_map<std::string, ResourceType> pool;
    std::string path;
    SDL_Renderer* renderer;
};

#endif // SHOVESTER_CORE_TEXTUREPOOL_H

