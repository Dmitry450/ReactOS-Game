#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <cassert>
#include <memory>
#include <string>

#include "PhysicalEntity.hpp"
#include "Inventory.hpp"
#include "Sprite.hpp"

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

        Inventory inventory;

        static const int hotbar_entries = 4;
        int hotbar_selected = 0;
        std::shared_ptr<ItemDef> hotbar[hotbar_entries];

        Entity *getEntity(GameState &game);

        Player(double _jump_force, double _accel, double _max_speed):
            jump_force(_jump_force), accel(_accel), max_speed(_max_speed) {

            inventory.resize(32);
        }
    };

    class PlayerEntity: public PhysicalEntity {
        Player *player = nullptr;
        Sprite sprite;

    public:
        using PhysicalEntity::PhysicalEntity;

        void update(GameState &game) override;
        void render(Display &d, Vector2i cam) override;

        inline void loadSprite(const std::string &path) {
            if (!sprite.load(path)) {
                // TODO - i need to handle such errors, not ignore
                //throw "bruh";
            }

            sprite.setAnimation("stand_right");
        }

        inline void assignPlayer(Player *player) {
            this->player = player;

            // Should add entity into manager before running this method
            assert(id != 0);
            player->entity_id = id;
        }
    };
}

#endif
