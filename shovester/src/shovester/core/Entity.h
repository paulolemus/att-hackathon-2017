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

    void addComponent(Component* comp) {
        if (components.find(comp) == comp.end()) {
            components.push_back(comp);
        } else {
            throw std::runtime_error("Could not add component to same vector");
        }
    }

    void removeComponent(Component* comp) {
        auto found = components.find(comp);
        if (found != comp.end()) {
            delete *found;
            components.erase(found);
        }
    }
      

private:
    std::string name;
    std::vector<Component*> components;
};

#endif // SHOVESTER_CORE_ENTITY_H
