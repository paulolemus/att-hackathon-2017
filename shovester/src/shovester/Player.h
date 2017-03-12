#ifndef SHOVESTER_CORE_PLAYER_H_
#define SHOVESTER_CORE_PLAYER_H_

#include <cmath>
#include <vector>
#include "shovester/core/Entity.h"
#include "shovester/core/Component.h"
#include "shovester/core/component/Physics.h"
#include "shovester/core/component/Sprite.h"

class Player : public Entity {
public:
    Player(std::vector<Component*> components) :
        Entity(components),
        maxSpeed(25),
        location({1280/2 - 64, 720/2 - 64, 128, 128}),
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
        float currX = dynamic_cast<Physics*>(getComponent(phys))->getX();
        float currY = dynamic_cast<Physics*>(getComponent(phys))->getY();
        float deltaX;
        float deltaY;
        if(!isAttacking){
            deltaX = x - currX;
            deltaY = y - currY;
            if(sqrt(deltaX * deltaX + deltaY * deltaY) > maxSpeed){
                float length = sqrt(deltaX * deltaX + deltaY * deltaY);
                deltaX /= length;
                deltaY /= length;
                deltaX *= maxSpeed;
                deltaY *= maxSpeed;
            }
            b2Vec2 vec(deltaX, deltaY);
            std::cout << "deltax/y: " <<  deltaX<< ',' << deltaY << std::endl;
            dynamic_cast<Physics*>(getComponent(phys))->applyImpulse(vec);
        }
    }

    void update(float delta){
        // Update the position of the box.
        this->location.x = dynamic_cast<Physics*>(getComponent(phys))->getX();
        this->location.y = dynamic_cast<Physics*>(getComponent(phys))->getY();

        std::cout << location.x << ',' << location.y << std::endl;
    }

    SDL_Rect& getLocationRect() { return this->location; }
    
private:
    SDL_Rect location; 
    std::string phys;
    std::string sprite;
    const float maxSpeed;
    bool isDead;
    bool isAttacking;
};

#endif
