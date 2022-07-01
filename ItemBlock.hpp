#ifndef ITEM_BLOCK_HPP_INCLUDED
#define ITEM_BLOCK_HPP_INCLUDED

#include <cstdint>

#include "Item.hpp"


namespace Game {

    class ItemBlock: public ItemController {
        uint16_t block;
    public:
        ItemBlock(uint16_t _block):
            block(_block)
        {}

        void onUse(ItemStack &istack, Player *player, Vector2d pos) override;
    };

}

#endif
