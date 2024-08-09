#include "Collider2D.hpp"

Collider2D::Collider2D() {
    m_box.x = 0;
    m_box.y = 0; 
    m_box.w = 0; 
    m_box.h = 0; 
}

Collider2D::Collider2D(int x, int y, int w, int h) {
    m_box.x = x; 
    m_box.y = y; 
    m_box.w = w; 
    m_box.h = h; 
} 
Collider2D::~Collider2D() {
    
}
void Collider2D::SetColliderBox(int x, int y, int w, int h) {
    m_box.x = x;
    m_box.y = y;
    m_box.w = w;
    m_box.h = h;
}
void Collider2D::SetColliderBoxAutomatically(int x, int y, SDL_Surface* surface, int r, int g, int b, int gameScale) {
    SDL_LockSurface(surface); 
    int w = surface->w;
    int h = surface->h;
    int pitch = surface->pitch;
    int colorChannels = pitch / w;
    Uint8* pixels = (Uint8*) surface->pixels;
    SDL_UnlockSurface(surface); 

    int xMax = 0; 
    int xMin = w; 
    int yMax = 0; 
    int yMin = h; 

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w * colorChannels; x += colorChannels) {
            if (pixels[y * (w * colorChannels) + x + 0] == b && 
                pixels[y * (w * colorChannels) + x + 1] == g &&
                pixels[y * (w * colorChannels) + x + 2] == r) {
            } else {
                xMin = std::min(x, xMin); 
                xMax = std::max(x, xMax); 
                yMin = std::min(y, yMin); 
                yMax = std::max(y, yMax); 
            }
        }
    int scale = w / gameScale; 
    m_box.w = (xMax / colorChannels - xMin / colorChannels) / scale; 
    m_box.h = (yMax - yMin) / scale; 
    m_box.x = x + (xMin / (colorChannels * scale));
    m_box.y = y + (yMin / scale);
}

SDL_bool Collider2D::Intersects(Collider2D* other) {
    return SDL_HasIntersection(&m_box, &(other->GetBox()));
}

