#ifndef CHUNK_HPP_INCLUDED
#define CHUNK_HPP_INCLUDED

#include <cstdint>

//#define CHUNK_WIDTH 4
//#define CHUNK_HEIGHT 4

class Chunk {

public:

    static const int width = 4, height = 4;

private:

    uint16_t data[width][height];

public:

    uint16_t* operator[](int pos) {
        return &data[pos][0];
    }

    Chunk(int x, int y) {

        uint16_t fillBlock = 0;

        if (y > 0) {
            if (y > 5) {
                fillBlock = 2;
            } else {
                fillBlock = 1;
            }
        }

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                data[x][y] = fillBlock;
            }
        }


    }

};


#endif // CHUNK_HPP_INCLUDED
