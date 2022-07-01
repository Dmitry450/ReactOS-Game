#include "ItemBlock.hpp"
#include "GameState.hpp"
#include "Tile.hpp"


namespace Game {
    void ItemBlock::onUse(ItemStack &istack, Player *player, Vector2d pos) {
        GameState *game = GameState::Instance();

        World &world = game->getWorld();

        int x = pos.x / TILE_WIDTH, y = pos.y / TILE_HEIGHT;

        if (world.get(x, y) != block) {
            world.set(x, y, block);

            istack.add(-1);
        }
    }
}
