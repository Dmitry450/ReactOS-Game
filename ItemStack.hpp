#ifndef ITEM_STACK_HPP_INCLUDED
#define ITEM_STACK_HPP_INCLUDED

#include <memory>

#include "Item.hpp"

namespace Game {

    class ItemStack {
        unsigned int count = 0;
        std::shared_ptr<ItemDef> def;

    public:
        inline void set(std::shared_ptr<ItemDef> def, unsigned int count = 1) {
            this->def = def;
            this->count = count;

            if (def) {
                this->count = std::min(count, def->max_count);
            }
        }

        int add(int change) {
            int left = 0;

            if (!def) {
                count += change;
                return left;
            }

            if (change < 0 && change > static_cast<int>(count)) {
                left = change + count;

                count = 0;
            } else if (change + count > def->max_count) {
                left = change + count - def->max_count;

                count = def->max_count;
            } else {
                count += change;
            }

            return left;
        }

        inline void merge(ItemStack &other) {
            if (!canMerge(other)) { return; }

            other.count = add(other.count);
        }

        inline void swap(ItemStack &other) {
            auto other_def = other.def;
            auto other_count = other.count;

            other.set(def, count);

            def = other_def;
            count = other_count;
        }

        inline bool canMerge(const ItemStack &other) {
            return def == other.def;
        }

        inline std::shared_ptr<ItemDef> getDef() {
            return def;
        }

        inline unsigned int getCount() {
            return count;
        }

        inline bool empty() {
            return !def || count == 0;
        }
    };

}

#endif
