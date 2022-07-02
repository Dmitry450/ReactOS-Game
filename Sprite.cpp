#include <stdexcept>
#include <sstream>

#include "Sprite.hpp"
#include "Color.hpp"
#include "Transparency.hpp"

namespace Game {

    bool Sprite::load(const std::string &path) {
        std::ifstream f(path);

        if (!f.is_open()) {
            return false;
        }

        anims.clear();

        std::string line;

        // First, read texture name, fg_color, bg_color and transparency
        if (!std::getline(f, line)) {
            return false;
        }

        if (!readTexture(line)) {
            return false;
        }

        // Then read animations.
        // Format: <name> <num_frames> <time_per_frame>
        while (std::getline(f, line)) {
            if (line.empty()) {
                continue;
            }

            if (!readAnimation(line, f)) {
                // Write some error. Currently do nothing because stdout
                // used as graphics and i don't have some in-game console.
            }
        }

        return true;
    }

    inline bool Sprite::readTexture(const std::string &info) {
        // reset
        texture = Texture();

        std::istringstream iss(info);

        std::string path;
        WORD color = 0;
        Transparency transparency;

        std::string input;

        // File path
        iss>>path;

        // Foreground color
        iss>>input;
        auto found = FG_COLOR_MAP.find(input);

        if (found != FG_COLOR_MAP.end()) {
            color |= found->second;
        } else {
            return false;
        }

        // Background color
        iss>>input;
        found = BG_COLOR_MAP.find(input);

        if (found != BG_COLOR_MAP.end()) {
            color |= found->second;
        } else {
            return false;
        }

        // Transparency
        iss>>input;
        auto tp_found = TRANSPARENCY_MAP.find(input);

        if (tp_found != TRANSPARENCY_MAP.end()) {
            transparency = tp_found->second;
        } else {
            return false;
        }

        texture.load(path.c_str());
        texture.setColor(color);
        texture.setTransparency(transparency);

        return true;
    }

    inline bool Sprite::readAnimation(const std::string &info, std::ifstream &f) {
        std::istringstream infos(info);

        std::string name;
        unsigned int num_frames;
        unsigned int time_per_frame;
        std::vector<Rect> rects;

        std::string input;

        infos>>name;

        infos>>input;

        try {
            num_frames = stoul(input);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        infos>>input;

        try {
            time_per_frame = stoul(input);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        for (unsigned int i = 0; i < num_frames; ++i) {
            Rect rect;

            if (!std::getline(f, input)) {
                return false;
            }

            if (input.empty()) {
                // num_framse is not used after this for loop, so it can
                // be changed to ignore empty lines
                ++num_frames;
                continue;
            }

            if (!storect(input, rect)) {
                return false;
            }

            rects.push_back(rect);
        }

        anims[name] = Animation();
        anims[name].rects = rects;
        anims[name].time_per_frame = time_per_frame;

        return true;
    }

    inline bool Sprite::storect(const std::string &s, Rect &rect) {
        std::istringstream iss(s);

        std::string input;

        iss>>input;
        try {
            rect.x = stoul(input);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        iss>>input;
        try {
            rect.y = stoul(input);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        iss>>input;
        try {
            rect.w = stoul(input);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        iss>>input;
        try {
            rect.h = stoul(input);
        } catch (const std::invalid_argument &e) {
            return false;
        }

        return true;
    }

    void Sprite::update() {
        if (current_anim != nullptr) {
            if (current_anim->timer != 0) {
                current_anim->timer--;
            } else {
                current_anim->frame++;

                if (current_anim->frame == current_anim->rects.size()) {
                    current_anim->frame = 0;
                }
            }
        }
    }

    void Sprite::render(Display &d, Vector2i pos) {
        if (current_anim == nullptr) {
            return;
        }

        Rect &rect = current_anim->rects[current_anim->frame];

        if (pos.x + rect.w < 0 || pos.x > d.getWidth() ||
            pos.y + rect.h < 0 || pos.y > d.getHeight()) {
            return;
        }

        texture.render(d, pos.x, pos.y, &rect);
    }

} // namespace Game
