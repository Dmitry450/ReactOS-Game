#ifndef INVENTORY_HPP_INCLUDED
#define INVENTORY_HPP_INCLUDED

#include <vector>
#include <memory>

#include "Item.hpp"
#include "ItemStack.hpp"

namespace Game {

    class Inventory {
        std::vector<ItemStack> items;

    public:
        inline void resize(unsigned int size) {
            items.resize(size);
        }

        inline unsigned int size() {
            return items.size();
        }

        inline ItemStack &get(unsigned int i) {
            return items.at(i);
        }

        void addItem(ItemStack &new_item);

        unsigned int countItems(std::shared_ptr<ItemDef> type);

        std::vector<std::shared_ptr<ItemDef>> uniqueItems();

        ItemStack *find(std::shared_ptr<ItemDef> type);
    };

}

#endif
