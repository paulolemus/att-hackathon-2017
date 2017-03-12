#ifndef SHOVESTER_CORE_COMPONENT_STRINGTABLE_H
#define SHOVESTER_CORE_COMPONENT_STRINGTABLE_H

#include <unordered_map>
#include <string>

#include "shovester/core/Component.h"

#include <SDL2/SDL.h>


template <typename Drawable>
class GUI : public Component {
public:
    GUI (std::string name, Drawable data) :
        name(name),
        data(data) {}

    std::string getName() const { return name; }

    void draw (SDL_Renderer* renderer, SDL_Rect rect) {
        data.draw(renderer, rect);            
    }

    Drawable& getData() { return data; }

private:
    std::string name;
    Drawable data;
};

#endif // SHOVESTER_CORE_COMPONENT_STRINGTABLE_H
