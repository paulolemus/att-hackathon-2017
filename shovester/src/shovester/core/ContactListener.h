#ifndef SHOVESTER_CORE_CONTACTLISTENER_H_
#define SHOVESTER_CORE_CONTACTLISTENER_H_

#include <iostream>
#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {

    void BeginContact(b2Contact* contact) {
        
        // check if fixture A was a entity
        std::cout << "Began contact" << std::endl;
    }

    void EndContact(b2Contact* contact) {

        std::cout << "End contact" << std::endl;
    }

};

#endif
