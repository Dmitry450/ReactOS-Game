#ifndef PHYSICAL_ENTITY_HPP_INCLUDED
#define PHYSICAL_ENTITY_HPP_INCLUDED

#include "Entity.hpp"
#include "Tile.hpp"
#include "Vector.hpp"

namespace Game {
    struct PhysicsParams {
        double gravity;

        double max_fall_speed;

        bool collision;
    };

    struct CollisionInfo {
        bool blocku;
        bool blockd;
        bool blockl;
        bool blockr;
    };

    class PhysicalEntity: public Entity {
        PhysicsParams physics;

        CollisionInfo collision_info = { false, false, false, false };

        Vector2d speed;

    public:
        PhysicalEntity(const Hitbox &hitbox, const PhysicsParams &_physics = { 0.05, 3.0, true },
                       const Vector2d &_speed = { 0, 0 }):
            Entity(hitbox), physics(_physics), speed(_speed)
        {}

        void update(GameState &game) override;

        void collide(GameState &game, bool by_x);

        inline CollisionInfo &getCollisionInfo() {
            return collision_info;
        }

        inline PhysicsParams &getPhysicsParams() {
            return physics;
        }

        inline Vector2d &getSpeed() {
            return speed;
        }

    };
}

#endif
