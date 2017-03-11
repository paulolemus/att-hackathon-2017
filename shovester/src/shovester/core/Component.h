#ifndef SHOVESTER_CORE_COMPONENT_H
#define SHOVESTER_CORE_COMPONENT_H

class Component {
public:
    virtual std::string getName() const = 0;

    virtual ~Component() {}

private:
};

#endif // SHOVESTER_CORE_COMPONENT_H
