#include "World.hpp"
#include <cstdlib>

void World::create(uint64_t seed) {
    // Generate world
    if (blocks != nullptr) {
        delete[] blocks;
    }

    blocks = new uint16_t[SIZE*SIZE];

    for (int x = 0; x < SIZE; ++x) {
        for (int y = 0; y < SIZE; ++y) {
            uint16_t block = 0;

            if (y > SIZE / 2) {
                block = 1;
            }

            if (y > SIZE * 3 / 4) {
                block = 2;
            }

            blocks[y*SIZE + x] = block;
        }
    }
}

uint16_t World::get(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        return 0;
    }

    return blocks[SIZE*y + x];
}

void World::set(int x, int y, uint16_t block) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        return;
    }

    blocks[SIZE*y + x] = block;
}
