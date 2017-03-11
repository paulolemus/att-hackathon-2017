#ifndef SHOVESTER_CORE_ENTITY_H
#define SHOVESTER_CORE_ENTITY_H

#include <string>
#include <vector>

#include "shovester/core/Component.h"

class Entity {
public:
    /// @brief Takes in a vector of Component objects
    ///        that are generic interfaces to individual
    ///        components.
    Entity(std::vector<Component*> components) : 
        components(components) {}



    Component* getComponent(std::string name) {
        for (auto it : components) {
            if (it->getName() == name) {
                return it;
            }
        }
    }
      

private:
    std::string name;
    std::vector<Component*> components;
};

#endif // SHOVESTER_CORE_ENTITY_H
