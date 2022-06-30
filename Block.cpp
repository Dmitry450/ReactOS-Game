#include <fstream>
#include <sstream>
#include <cctype>
#include <stdexcept>

#include "Block.hpp"

namespace Game {

    BlockDefManager::BlockDefManager() {
        atlas.getTexture().setBackground('\0');
    }

    bool BlockDefManager::load(const char *path) {
        defs.clear();

        std::ifstream f(path);

        if (!f.is_open()) {
            return false;
        }

        int lineno = 1;

        std::string line;

        while (std::getline(f, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }

            // Skip comments
            if (line.front() == '#') {
                continue;
            }

            if (!readDef(line)) {
                // Uh oh, how do i write to stdout if it is used as graphics
                //std::cout<<path<<":"<<lineno<<": Malformed block def: "<<line<<std::endl;
            }

            ++lineno;
        }

        f.close();

        return true;
    }

    BlockDef &BlockDefManager::getDef(uint16_t id) {
        --id;

        if (id >= defs.size()) {
            return unknown;
        }

        return defs[id];
    }

    bool BlockDefManager::readDef(std::string &line) {
        // Line format: <texture path> <fg color> <bg color> <is solid>
        Rect texture_rect;
        WORD color = 0;
        bool solid;

        std::istringstream f(line);

        std::string input; // Buffer for string input

        // Texture path
        f>>input;

        if (!atlas.isLoaded(input)) {
            if (!atlas.load(input)) {
                return false;
            }
        }

        texture_rect = atlas.getRect(input);

        // Foreground color
        f>>input;
        auto found = FG_COLOR_MAP.find(input);

        if (found != FG_COLOR_MAP.end()) {
            color |= found->second;
        } else {
            return false;
        }

        // Background color
        f>>input;
        found = BG_COLOR_MAP.find(input);

        if (found != BG_COLOR_MAP.end()) {
            color |= found->second;
        } else {
            return false;
        }

        // Is solid
        f>>input;

        // Ignore case
        for (auto& c : input) {
            c = std::tolower(c);
        }

        solid = input == "true";

        BlockDef def = {
            color,
            texture_rect,
            solid,
        };

        defs.push_back(def);

        return true;
    }

}
