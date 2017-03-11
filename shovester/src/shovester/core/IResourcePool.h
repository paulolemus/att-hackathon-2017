#ifndef SHOVESTER_CORE_IRESOURCEPOOL_H
#define SHOVESTER_CORE_IRESOURCEPOOL_H

#include <string>

template <typename ResourceType>
class IResourcePool {
public:

    virtual void loadResource (std::string key, std::string label = "") = 0;
    virtual void unloadResource (std::string label) = 0;
    virtual ResourceType getResource (std::string label) = 0;
    void setPath (std::string path) { this->path = path; }

private:
    std::string path;
};

#endif // SHOVESTER_CORE_IRESOURCEPOOL_H

