#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <cstdint>

#include "Hitbox.hpp"
#include "Display.hpp"

// Forward declaration
class GameState;

namespace Game {
    class Entity {
    protected:
        uint16_t id = 0;

    public:
        Hitbox hitbox;

        explicit Entity(const Hitbox &_hitbox):
            hitbox(_hitbox)
        {}

        void setId(uint16_t id) { this->id = id; }
        uint16_t getId() { return id; }

        virtual void update(GameState &game) {}
    };
}

#endif // ENTITY_HPP_INCLUDED
