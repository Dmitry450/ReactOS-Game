#include <fstream>
#include <stdexcept>

#include "TextureAtlas.hpp"

namespace Game {
    bool TextureAtlas::load(const std::string &path) {
        if (isLoaded(path)) {
            return true;
        }

        std::ifstream f(path);
        Rect rect = {0, texture.getHeight(), 0, 0};

        if (!f.is_open()) {
            return false;
        }

        std::string line;

        while (std::getline(f, line)) {
            texture.appendLine(line);

            if (line.length() > rect.w) {
                rect.w = line.length();
            }

            rect.h++;
        }

        rects[path] = rect;

        f.close();

        return true;
    }

    Rect TextureAtlas::getRect(const std::string &path) {
        if (!isLoaded(path)) {
            std::string err = "No such texture in atlas: ";
            err += path;
            throw std::invalid_argument(err);
        }

        return rects[path];
    }
}
