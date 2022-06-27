#ifndef TEXTURE_ATLAS_HPP_INCLUDED
#define TEXTURE_ATLAS_HPP_INCLUDED

#include <string>
#include <map>

#include "Texture.hpp"
#include "Rect.hpp"

namespace Game {
    class TextureAtlas {
        Texture texture;
        std::map<std::string, Rect> rects;

        public:
            bool load(const std::string &path);

            Rect getRect(const std::string &path);

            const Texture &getTexture() { return texture; }
    };
}

#endif
