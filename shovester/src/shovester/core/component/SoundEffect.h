#ifndef SHOVESTER_CORE_COMPONENT_SOUNDEFFECT_H
#define SHOVESTER_CORE_COMPONENT_SOUNDEFFECT_H

#include <string>

#include <SDL2/SDL_mixer.h>

#include "shovester/core/Component.h"

class SoundEffect : public Component {
public:

    SoundEffect (std::string name, 
                 Mix_Chunk*  soundEffect) :
        soundEffect(soundEffect),
        name(name) {}

    std::string getName() const { return this->name; }

    Mix_Chunk* get () const {
       return this->soundEffect; 
    }

    void set (Mix_Chunk* soundEffect) {
        if (soundEffect) {
            this->soundEffect = soundEffect;
        } else {
            throw std::runtime_error("SoundEffect: set() soundEffect is nullptr");
        }
    }

    /// @brief Returns whether it successfully played
    ///        the sound or not. Use channel -1 to get
    ///        the first available channel.
    bool play (int channel,
               int volume,
               int loops = 0) {
        Mix_VolumeChunk(this->soundEffect, volume);
        return (
            Mix_PlayChannel(
                channel,
                this->soundEffect,
                loops
            ) != -1
        ); 
    }

private:
    Mix_Chunk* soundEffect;
    std::string name;
};

#endif // SHOVESTER_CORE_COMPONENT_SOUNDEFFECT_H
