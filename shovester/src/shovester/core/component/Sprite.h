#ifndef SHOVESTER_CORE_COMPONENT_SPRITE_H
#define SHOVESTER_CORE_COMPONENT_SPRITE_H 

#include <vector>
#include <string>

#include "shovester/core/Component.h"

#include <SDL2/SDL.h>

class Sprite : public Component {
public:
    Sprite (std::string name, SDL_Texture* texture, std::vector<SDL_Rect> boxes) :
        name(name),
        texture(texture),
        boxes(boxes),
        frameNo(0),
        rotation(0) {}

    SDL_Texture* getTexture () const {
        return this->texture;
    }

    void setTexture (SDL_Texture* texture) {
        this->texture = texture;
    }

    std::size_t getNumFrames() const {
        return boxes.size();
    }

    void nextFrame() {
        frameNo = (frameNo + 1) % boxes.size();
    }

    const SDL_Rect& getRect() {
        return boxes[frameNo];
    }

    void setRotation(double degrees) {
        this->rotation = degrees;
    }

    double getRotation() const {
        return this->rotation;
    }

    std::string getName() const { return name; }

private:
    std::string name;
    SDL_Texture* texture;
    std::vector<SDL_Rect> boxes;
    int frameNo;
    double rotation;
};

#endif // SHOVESTER_CORE_COMPONENT_SPRITE_H
