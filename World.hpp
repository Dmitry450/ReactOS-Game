#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "Entity.hpp"
#include <vector>
#include <cstdint>

class World {
    uint16_t* blocks = nullptr;

public:
    static const int SIZE = 2048;

    void create(uint64_t seed = 1234567890);
    void load(const char* path);

    uint16_t get(int x, int y);

    void set(int x, int y, uint16_t block);

    ~World() {
        if (blocks != nullptr) {
            delete[] blocks;
        }
    }

};

#endif // WORLD_HPP_INCLUDED
