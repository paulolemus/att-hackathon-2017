#ifndef SHOVESTER_CORE_MIXCHUNKPOOL_H
#define SHOVESTER_CORE_MIXCHUNKPOOL_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "shovester/core/IResourcePool.h"

/// @brief Holds SDL_mixer's Mix_Chunk*, and loads it from
///        files, prefixed by the path.
template <typename ResourceType = Mix_Chunk*>
class MixChunkPool : public IResourcePool<ResourceType> {
public:
    /// @brief Assumes that the Mix_OpenAudio was already
    ///        called by an external subsystem.
    MixChunkPool(std::string path) :
        path(path) {}

    virtual void loadResource (std::string key, std::string label = "") override {
        Mix_Chunk* chunk = NULL;

        // If you cannot load a file with that key name from the
        // current execution environment, instead, look for it in
        // the path.
        if ((chunk = Mix_LoadWAV(key.c_str())) == NULL) {
            chunk = Mix_LoadWAV((path + key).c_str());
        }

        // If the surface could not be loaded, throw an error.
        if (chunk == NULL) {
            std::string str("Could not load mixer audio chunk file: ");
            str += path;
            str += key;
            throw std::runtime_error(str.c_str());

        // Otherwise, create an SDL_Texture* from the SDL_Surface*
        // using the SDL texture.
        } else {
            // If the label is nothing, just use the key as the label
            if (label == "") {
                label = key;
            }
            if (pool.find(label) == pool.end()) {
                pool[label] = chunk;
            } else {
                std::string str("Cannot insert onto existing key: ");
                str += key;
                throw std::runtime_error(str.c_str());
            }
        }
    }

    /// @brief Unloads the resource only if it is there.
    virtual void unloadResource (std::string label) override {
        // Only unload the resource if it matches the key.
        auto element = pool.find(label);
        if (element != pool.end()) {
            Mix_FreeChunk(pool[label]);
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

    ~MixChunkPool() {
        // Free the chunk samples.
        for (auto it : pool) {
            Mix_FreeChunk(it.second);
        }
    }

private:
    std::unordered_map<std::string, ResourceType> pool;
    std::string path;
};

#endif // SHOVESTER_CORE_TEXTUREPOOL_H