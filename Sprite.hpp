#ifndef SPRITE_HPP_INCLUDED
#define SPRITE_HPP_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "Texture.hpp"
#include "Vector.hpp"

namespace Game {

    struct Animation {
        std::vector<Rect> rects;

        unsigned int timer = 0;
        unsigned int time_per_frame = 0;

        unsigned int frame = 0;
    };

    class Sprite {
        Texture texture;

        std::map<std::string, Animation> anims;

        Animation *current_anim = nullptr;
        std::string current_anim_name;

        // inline them because they are used only once
        inline bool readTexture(const std::string &info);
        inline bool readAnimation(const std::string &info, std::ifstream &f);
        inline bool storect(const std::string &s, Rect &rect);

    public:
        bool load(const std::string &path);

        void update();

        void render(Display &d, Vector2i pos);

        inline void addAnimation(const std::string &name, const Animation &animation) {
            anims[name] = animation;
        }

        inline Texture &getTexture() { return texture; }

        void setAnimation(const std::string &name, bool restart = false) {
            current_anim_name = name;

            auto pair = anims.find(name);

            if (pair == anims.end()) {
                current_anim = nullptr;
                return;
            }

            current_anim = &pair->second;

            if (restart) {
                current_anim->timer = current_anim->time_per_frame;
                current_anim->frame = 0;
            }
        }

        inline const std::string &getCurrentAnimation() {
            return current_anim_name;
        }

    };

}

#endif
