#ifndef SHOVESTER_CORE_COMPONENT_STRINGTABLE_H
#define SHOVESTER_CORE_COMPONENT_STRINGTABLE_H

#include <unordered_map>
#include <string>

#include "shovester/core/Component.h"

class StringTable : public Component {
    StringTable(std::string name) :
        name(name) {}

    std::string get(std::string key) const {
        auto found = table.find(key);
        if (found != table.end()) {
            return found->second;
        } else {
            return "";
        }
    }

    void set(std::string key, std::string value) {
        table[key] = value;
    }

    bool contains (std::string key) const {
        return (table.find(key) != table.end());
    }

    std::string getName() const { return name; }

private:
    std::string name;
    std::unordered_map<std::string, std::string> table;
};

#endif // SHOVESTER_CORE_COMPONENT_STRINGTABLE_H