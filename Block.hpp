#ifndef BLOCK_HPP_INCLUDED
#define BLOCK_HPP_INCLUDED

#include <vector>
#include <string>

#define NOMINMAX
#include <windows.h>

#include "Rect.hpp"


namespace Game {

    struct BlockDef {
        WORD color;
        Rect texture_rect;
        bool solid;
    };

    class BlockDefManager {
        std::vector<BlockDef> defs;
        BlockDef unknown;

    public:
        BlockDefManager();

        // Loads block defs from a file.
        // It ignores (but warns about) all malformed entries
        bool load(const char *path);

        // Returns block def associated with id or returns unknown block def
        // if id is out of range
        BlockDef &getDef(int id);

    private:
        bool readDef(std::string &line);
    };

}

#endif // BLOCK_HPP_INCLUDED
