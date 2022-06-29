#include "PhysicalEntity.hpp"
#include "GameState.hpp"


namespace Game {
    void PhysicalEntity::update(GameState &game) {
        if (!collision_info.blockd) {
            speed.y = std::min(physics.max_fall_speed, speed.y + physics.gravity);
        }

        hitbox.x += speed.x;
        if (physics.collision) {
            collide(game, true);
        }

        hitbox.y += speed.y;
        if (physics.collision) {
            collide(game, false);
        }
    }

    void PhysicalEntity::collide(GameState &game, bool by_x) {
        if (by_x) {
            collision_info.blockl = false;
            collision_info.blockr = false;
        } else {
            collision_info.blocku = false;
            collision_info.blockd = false;
        }

        int y_min = hitbox.top()/TILE_HEIGHT;
        float y_max = hitbox.bottom()/TILE_HEIGHT;

        int x_min = hitbox.left()/TILE_WIDTH;
        float x_max = hitbox.right()/TILE_WIDTH;

        World &world = game.getWorld();
        BlockDefManager &block_defs = game.getBlockDefs();

        for (int y = y_min; y < y_max; y++)
        {
            for (int x = x_min; x < x_max; x++)
            {
                uint16_t block = world.get(x, y);

                if (!block) {
                    continue;
                }

                if (block_defs.getDef(block).solid) {
                    if (by_x) {
                        if (speed.x > 0) {
                            hitbox.x = x*TILE_WIDTH - hitbox.w;
                            collision_info.blockr = true;
                        } else {
                            hitbox.x = (x+1)*TILE_WIDTH;
                            collision_info.blockl = true;
                        }

                        speed.x = 0;
                    } else {
                        if (speed.y > 0) {
                            hitbox.y = y*TILE_HEIGHT - hitbox.h;
                            collision_info.blockd = true;
                        } else {
                            hitbox.y = (y+1)*TILE_HEIGHT;
                            collision_info.blocku = true;
                        }

                        speed.y = 0;
                    }
                }
            }
        }
    }
}
