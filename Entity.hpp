#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <cstdint>

#include "Hitbox.hpp"

namespace Game {
    class Entity {
        uint16_t id = 0;

    public:
        Hitbox hitbox;

        Entity(Hitbox _hitbox):
            hitbox(_hitbox)
        {}

        void setId(uint16_t id) { this->id = id; }
        uint16_t getId() { return id; }

        virtual void update() {}
    };
}

#endif // ENTITY_HPP_INCLUDED
