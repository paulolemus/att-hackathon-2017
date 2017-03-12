#ifndef SHOVESTER_CORE_TEXT_H
#define SHOVESTER_CORE_TEXT_H

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Font {
    public:
        Font(std::string path, size_t size = 12) :
            font(nullptr) {
            this->openFont(path, size);
        }

        ~Font() {
            TTF_CloseFont(font);
        }

        void openFont(std::string path, size_t size = 12) {
            font = TTF_OpenFont(path.c_str(), size);

            if (font == nullptr) {
                std::cout << "Failed to load font from " << path << "; " << TTF_GetError() << std::endl;
                throw std::runtime_error(TTF_GetError());
            } else {
                return;
            }
        }

        TTF_Font* getFont() {return font;}

    private:
        TTF_Font* font;
};  

class Text {
    public:
        Text(Font& font, SDL_Color color) :
            font(font),
            color(color) { texture = nullptr; }

        ~Text() {
            SDL_DestroyTexture(texture);
        }

        void setText (std::string str) {
           this->str = str; 
        }

        void draw (SDL_Renderer* renderer, SDL_Rect rect) {
            // Destroy the last texture if we can.
            if (texture != nullptr) {
                SDL_DestroyTexture(texture);
            }

            // Create the surface
            SDL_Surface* text_surface = TTF_RenderText_Blended(font.getFont(), str.c_str(), color);

            if (text_surface == nullptr) {
                std::cout << "Unable to render text surface; text: " << str << "; " << TTF_GetError() << std::endl;
                SDL_FreeSurface(text_surface);
                throw std::runtime_error(TTF_GetError());
            } else {
                // Create the texture from the surface.
                texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                if (texture == nullptr) {
                    std::cout << "Unable to create texture from text surface; text: " << str << "; " << SDL_GetError() << std::endl;
                    SDL_FreeSurface(text_surface);
                    throw std::runtime_error(SDL_GetError()); 
                } else {
                    // If successful, set the bounds.
                    bounds.x = 0;
                    bounds.y = 0;
                    bounds.w = text_surface->w;
                    bounds.h = text_surface->h;
                    // Free the surface.
                    SDL_FreeSurface(text_surface);

                    // Now, draw the texture.
                    SDL_RenderCopy(
                        renderer,
                        texture,
                        &bounds,
                        &rect
                    );
                }
            }
        }

        SDL_Texture* getTexture() { return texture; }
        SDL_Rect getRect() const { return bounds; }

    private:
        SDL_Rect bounds;
        std::string str;
        SDL_Renderer* renderer;
        Font& font;
        SDL_Color color;
        SDL_Texture* texture;
};

#endif // SHOVESTER_CORE_TEXT_H
