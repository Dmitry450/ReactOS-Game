#include <algorithm>

#include "Inventory.hpp"

namespace Game {

    void Inventory::addItem(ItemStack &new_item) {
        // First, try to find non-empty item stacks to merge
        for (auto &item: items) {
            item.merge(new_item);

            if (new_item.empty()) {
                return;
            }
        }

        // If new_item is still not empty, try to merge it with empty
        // item stacks
        for (auto &item: items) {
            if (item.empty()) {
                item.swap(new_item);
            }
        }
    }

    unsigned int Inventory::countItems(std::shared_ptr<ItemDef> type) {
        unsigned int result = 0;

        for (auto item: items) {
            if (item.getDef() == type) {
                result += item.getCount();
            }
        }

        return result;
    }

    std::vector<std::shared_ptr<ItemDef>> Inventory::uniqueItems() {
        std::vector<std::shared_ptr<ItemDef>> result;

        for (auto &item: items) {
            std::shared_ptr<ItemDef> item_def = item.getDef();

            // If result isn't containing this item def, add it
            if (!std::any_of(result.cbegin(), result.cend(),
                [&item_def](const std::shared_ptr<ItemDef> &udef){ return udef == item_def; })) {

                result.push_back(item_def);
            }
        }

        return result;
    }

    ItemStack *Inventory::find(std::shared_ptr<ItemDef> type) {
        for (auto &item: items) {
            if (item.getDef() == type) {
                return &item;
            }
        }

        return nullptr;
    }

}
