#ifndef SHOVESTER_CORE_COMPONENT_CONTROLLER_H
#define SHOVESTER_CORE_COMPONENT_CONTROLLER_H

#include <string>

#include "shovester/core/Component.h"

/// @brief Should be only updated once per update cycle.
template <typename ReactiveData>
class Controller : public Component {
public:

    virtual std::string getName() const override {
        return this->name;    
    }

    Controller(std::string name, ReactiveData rdata) :
        name(name),
        updatedFlag(false),
        data(rdata) {}

    void setData(ReactiveData rdata) {
        updatedFlag = true;
        this->data = rdata;
    }

    ReactiveData& getData() {
        updatedFlag = false;
        return this->data;
    }

    bool wasUpdated() const {
        return this->updatedFlag;
    }

private:
    std::string name;
    bool updatedFlag;
    ReactiveData data;
};

#endif // SHOVESTER_CORE_COMPONENT_CONTROLLER_H
