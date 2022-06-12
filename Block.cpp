#include <fstream>
#include <sstream>
#include <cctype>
#include <stdexcept>

#include "Block.hpp"
#include "Color.hpp"
#include "Tile.hpp"

namespace Game {

    BlockDefManager::BlockDefManager() {
        unknown = {
            Color::FG_RED | Color::BG_WHITE,
            { 0, 0, TILE_WIDTH, TILE_HEIGHT },
            true,
        };
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

    BlockDef &BlockDefManager::getDef(int id) {
        --id;

        if (id < 0 || id >= defs.size()) {
            return unknown;
        }

        return defs[id];
    }

    bool BlockDefManager::readDef(std::string &line) {
        // Line format: <texture index> <fg color> <bg color> <is solid>
        int texture_index;
        WORD color = 0;
        bool solid;

        std::istringstream f(line);

        std::string input; // Buffer for string input

        // Texture index
        f>>input;

        try {
            texture_index = stoi(input);
        } catch (std::invalid_argument const& ex) {
            return false;
        }

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
            { 0, texture_index * TILE_HEIGHT + texture_index, TILE_WIDTH, TILE_HEIGHT },
            solid,
        };

        defs.push_back(def);

        return true;
    }

}
