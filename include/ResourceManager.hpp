#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string> 

#include <SDL.h>

class ResourceManager {
    public: 
        static ResourceManager& GetInstance();
        SDL_Surface* GetSurface(std::string filepath);
    private: 
        ResourceManager();
        ResourceManager(ResourceManager const&);
        ResourceManager operator=(ResourceManager const&);
        ~ResourceManager();
        std::unordered_map<std::string, SDL_Surface*> m_surfaces; 
};

#endif
