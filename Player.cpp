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

        if (!player->left && !player->right) {
            speed.x *= player->friction;
        }

        if (player->jump && getCollisionInfo().blockd) {
            speed.y = -player->jump_force;
        }

        if (player->lmb || player->rmb) {
            int x = (player->mouse.x + hitbox.x)/TILE_WIDTH;
            int y = (player->mouse.y + hitbox.y)/TILE_HEIGHT;

            game.getWorld().set(x, y, player->rmb ? 1 : 0);
        }
    }
}
