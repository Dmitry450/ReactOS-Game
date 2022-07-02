#include "Player.hpp"
#include "GameState.hpp"

namespace Game {
    Entity *Player::getEntity(GameState &game) {
        return game.getEntityManager().getEntity(entity_id);
    }

    void PlayerEntity::update(GameState &game) {
        PhysicalEntity::update(game);

        if (player == nullptr) {
            return;
        }

        Vector2d &speed = getSpeed();

        if (player->left) {
            speed.x = std::max(-player->max_speed, speed.x - player->accel);
        }

        if (player->right) {
            speed.x = std::min(player->max_speed, speed.x + player->accel);
        }

        if (player->jump && getCollisionInfo().blockd) {
            speed.y = -player->jump_force;
        }

        if (player->lmb || player->rmb) {
            auto &def = player->hotbar[player->hotbar_selected];

            if (!def) {
                return;
            }

            ItemStack *istack = player->inventory.find(def);

            if (istack == nullptr) {
                return;
            }

            if (!istack->empty()) {
                Vector2d pos = { player->mouse.x + hitbox.x, player->mouse.y + hitbox.y };

                istack->getDef()->controller->onUse(*istack, player, pos);
            }
        }

        sprite.update();

        if (speed.x < -0.05) {
            sprite.setAnimation("walk_left");
        }

        if (speed.x > 0.05) {
            sprite.setAnimation("walk_right");
        }

        if (speed.x < 0.05 && speed.x > -0.05) {
            if (sprite.getCurrentAnimation() == "walk_left") {
                sprite.setAnimation("stand_left");
            } else if (sprite.getCurrentAnimation() == "walk_right") {
                sprite.setAnimation("stand_right");
            }
        }
    }

    void PlayerEntity::render(Display &d, Vector2i cam) {
        sprite.render(d, {
            static_cast<int>(hitbox.x) - cam.x,
            static_cast<int>(hitbox.y) - cam.y });
    }
} // namespace Game
