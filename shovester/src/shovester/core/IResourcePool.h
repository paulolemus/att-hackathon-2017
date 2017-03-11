#ifndef SHOVESTER_CORE_IRESOURCEPOOL_H
#define SHOVESTER_CORE_IRESOURCEPOOL_H

#include <string>
#include <unordered_map>

template <typename ResourceType>
class IResourcePool {
public:

    virtual void loadResource (std::string key) = 0;
    virtual void unloadResource (std::string key) = 0;
    virtual ResourceType getResource (std::string key) = 0;
    void setPath (std::string path) { this->path = path; }

private:
    std::unordered_map<std::string, ResourceType> pool;
    std::string path;
};

#endif // SHOVESTER_CORE_IRESOURCEPOOL_H

