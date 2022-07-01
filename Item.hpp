#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

#include <memory>
#include <string>
#include <map>

#include "Vector.hpp"


namespace Game {

    // Forward declarations
    class ItemStack;

    class Player;

    class ItemController {
    public:
        virtual void onUse(ItemStack &istack, Player *player, Vector2d pos) = 0;
    };

    struct ItemDef {
        std::string name;
        std::string description = "Default Description";
        unsigned int max_count = 999;
        std::unique_ptr<ItemController> controller;
    };

    class ItemDefManager {
        std::map<std::string, std::shared_ptr<ItemDef>> defs;

    public:
        void registerItem(std::shared_ptr<ItemDef> def) {
            defs[def->name] = def;
        }

        std::shared_ptr<ItemDef> getDef(const std::string &name) {
            auto pair = defs.find(name);

            if (pair == defs.end()) {
                return nullptr;
            }

            return pair->second;
        }
    };

}

#endif
