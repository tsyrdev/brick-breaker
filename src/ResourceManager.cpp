#include "ResourceManager.hpp"

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager* s_instance = new ResourceManager(); 
    return *s_instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath) {
    auto it = m_surfaces.find(filepath);  
    if (it != m_surfaces.end())
        return it->second; 
    else {
        SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
        m_surfaces.insert(std::make_pair(filepath, surface)); 
        return surface; 
    }
}
ResourceManager::ResourceManager() {

}
ResourceManager::ResourceManager(ResourceManager const&) {
    
}
ResourceManager ResourceManager::operator=(ResourceManager const&) {
    return *this; 
}
ResourceManager::~ResourceManager() {
    for (auto it = m_surfaces.begin(); it != m_surfaces.end(); ++it)
        delete it->second; 
}
std::unordered_map<std::string, SDL_Surface*> m_surfaces; 

