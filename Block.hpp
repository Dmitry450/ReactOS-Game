#ifndef BLOCK_HPP_INCLUDED
#define BLOCK_HPP_INCLUDED

#include <vector>
#include <string>
#include <cstdint>

#include <windows.h>

#include "Rect.hpp"
#include "TextureAtlas.hpp"
#include "Color.hpp"
#include "Tile.hpp"


namespace Game {

    struct BlockDef {
        WORD color;
        Rect texture_rect;
        bool solid;
    };

    class BlockDefManager {
        std::vector<BlockDef> defs;
        BlockDef unknown = {
            Color::FG_RED | Color::BG_WHITE,
            { 0, 0, TILE_WIDTH, TILE_HEIGHT },
            true,
        };

        TextureAtlas atlas;

    public:
        BlockDefManager();

        // Loads block defs from a file.
        // It ignores (but warns about) all malformed entries
        bool load(const char *path);

        // Returns block def associated with id or returns unknown block def
        // if id is out of range
        BlockDef &getDef(uint16_t id);

        inline TextureAtlas &getAtlas() { return atlas; }

    private:
        bool readDef(std::string &line);
    };

}

#endif // BLOCK_HPP_INCLUDED
