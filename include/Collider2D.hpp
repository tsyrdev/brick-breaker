#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL.h>
#include <algorithm>

class Collider2D {
    public: 
        Collider2D();
        Collider2D(int x, int y, int w, int h);
        ~Collider2D();
        void SetColliderBox(int x, int y, int w, int h);
        void SetColliderBoxAutomatically(int x, int y, SDL_Surface* surface, int r, int g, int b, int gameScale);
        const SDL_Rect& GetBox() { return m_box; }
        SDL_bool Intersects(Collider2D* other);
    private: 
        SDL_Rect m_box;
};

#endif
