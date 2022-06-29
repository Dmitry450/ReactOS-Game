#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <cassert>

#include "PhysicalEntity.hpp"

namespace Game {
    struct Player {
        bool left = false;
        bool right = false;
        bool down = false; // Maybe for platforms?

        bool jump = false;

        bool lmb = false;
        bool rmb = false;

        Vector2i mouse = { 0, 0 };

        double jump_force;
        double accel;

        double max_speed;

        uint16_t entity_id = 0;

        // Maybe some other data

        Entity *getEntity(GameState &game);

        Player(double _jump_force, double _accel, double _max_speed):
            jump_force(_jump_force), accel(_accel), max_speed(_max_speed)
        {}
    };

    class PlayerEntity: public PhysicalEntity {
        Player *player = nullptr;

    public:
        PlayerEntity(const Hitbox &hitbox, const PhysicsParams &_physics = { 0.05, 3.0, true },
                     const Vector2d &_speed = { 0, 0 }):
            PhysicalEntity(hitbox, _physics, _speed)
        {}

        void update(GameState &game) override;

        inline void assignPlayer(Player *player) {
            this->player = player;

            // Should add entity into manager before running this method
            assert(id != 0);
            player->entity_id = id;
        }
    };
}

#endif
