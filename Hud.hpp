#ifndef HUD_HPP_INCLUDED
#define HUD_HPP_INCLUDED

#include <vector>
#include <memory>

#include "Item.hpp"
#include "Player.hpp"
#include "Display.hpp"

// Forward declaration
class GameState;

namespace Game {

    struct InventoryEntry {
        std::shared_ptr<ItemDef> item_def;
        unsigned int count = 0;

        inline bool isEmpty() {
            return !item_def || count == 0;
        }
    };

    class Hud {
        enum HudState {
            NONE,
            INVENTORY,
        };

        HudState state = HudState::NONE;

        // Hotbar
        static const int hotbar_y = 1;

        struct {
            std::vector<InventoryEntry> entries;

            unsigned int selected = 0;

            const int height = 9;

            const int y = hotbar_y + Player::hotbar_entries + 1;
        } inventory;

        void inventory_reset(GameState &game);

    public:
        void render(GameState &game, Display &d);
        void update(GameState &game);

        // TODO - make some HudEntry class which will contain
        // rendering and updating code.
        void hotbar_render(GameState &game, Display &d);
        void hotbar_update(GameState &game);

        void inventory_render(GameState &game, Display &d);
        void inventory_update(GameState &game);
    };

}

#endif
