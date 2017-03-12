#ifndef SHOVESTER_CORE_COMPONENT_PHYSICS_H
#define SHOVESTER_CORE_COMPONENT_PHYSICS_H 

#include <string>

#include "shovester/core/Component.h"

#include <Box2D/Box2D.h>

class Physics : public Component {
public:
    Physics (std::string name, b2World* world, b2BodyDef bodyDef, b2FixtureDef fixDef) :
        name(name),
        world(world),
        bodyDef(bodyDef),
        fixDef(fixDef) {
        
            body = world->CreateBody(&bodyDef);
            body->CreateFixture(&fixDef);
            body->SetLinearDamping(1);
        }

    b2Vec2 getPosition() const { return body->GetPosition(); }
    float getX(){ return body->GetWorldCenter().x; }
    float getY(){ return body->GetWorldCenter().y; }

    void applyImpulse(b2Vec2& vec){
        body->ApplyLinearImpulse(vec, body->GetWorldCenter(), true);
    }
    void applyImpulse(float x, float y){
        body->ApplyLinearImpulse(b2Vec2(x, y), body->GetWorldCenter(), true);
    }

    void stop(){ body->SetLinearVelocity(b2Vec2(0, 0)); }

    b2Body* getBody() { return body; }
    std::string getName() const { return name; }

private:
    std::string name;
    b2World* world;
    b2Body*  body;
    b2BodyDef bodyDef;
    b2FixtureDef fixDef;

};

#endif // SHOVESTER_CORE_COMPONENT_PHYSICS_H
