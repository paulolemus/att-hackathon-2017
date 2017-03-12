#ifndef SHOVESTER_CORE_PLAYER_H_
#define SHOVESTER_CORE_PLAYER_H_

#include <vector>
#include "Entity.h"
#include "core/Component.h"
#include "core/component/Physics.h"
#include "core/component/Sprite.h"

class Player : public Entity {
public:
    Player(std::vector<Component*> components) :
        Entity(components),
        isDead(false),
        isAttacking(false)
    {
        for(int i = 0; i < components.size(); ++i){
            auto ptr = dynamic_cast<Sprite*>(components[i]);
            if(ptr){
                sprite = ptr->getName();
                i += components.size();
            }
        }
        for(int i = 0; i < components.size(); ++i){
            auto ptr = dynamic_cast<Physics*>(components[i]);
            if(ptr){
                phys = ptr->getName();
                i += components.size();
            }
        }
    }

    void move(float x, float y){
        
        if(!isAttacking){

        }
    }
    
private:
    std::string phys;
    std::string sprite;
    bool isDead;
    bool isAttacking;
};

#endif
