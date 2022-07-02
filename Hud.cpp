#include <sstream>

#include "Hud.hpp"
#include "GameState.hpp"

namespace Game {

    void Hud::render(GameState &game, Display &d) {
        switch (state) {
            case HudState::INVENTORY:
                inventory_render(game, d);
            break;

            case HudState::NONE:
            break;
        }

        // Always render hotbar
        hotbar_render(game, d);
    }

    void Hud::update(GameState &game) {
        switch (state) {
            case HudState::INVENTORY:
                inventory_update(game);
            break;

            case HudState::NONE: {
                hotbar_update(game);

                KeyHandler &key_handler = game.getKeyHandler();

                // 0x49 - I
                if (key_handler.isJustPressed(0x49)) {
                    inventory_reset(game);
                    state = HudState::INVENTORY;
                }
            }
            break;
        }
    }

    void Hud::hotbar_render(GameState &game, Display &d) {
        Player &player = game.getPlayer();

        std::ostringstream oss;

        for (int i = 0; i < player.hotbar_entries; ++i) {
            oss.str("");
            oss.clear();

            unsigned int item_count = player.inventory.countItems(player.hotbar[i]);

            if (i == player.hotbar_selected) {
                oss<<"> ";
            }

            if (item_count == 0 || !player.hotbar[i]) {
                oss<<"(none)";
            } else {
                oss<<player.hotbar[i]->description;

                if (item_count > 1) {
                    oss<<" (x"<<item_count<<")";
                }
            }

            d.writeString(oss.str().c_str(), 1, hotbar_y+i);
        }
    }

    void Hud::hotbar_update(GameState &game) {
        Player &player = game.getPlayer();
        KeyHandler &key_handler = game.getKeyHandler();

        if (key_handler.isJustPressed(VK_DOWN)) {
            player.hotbar_selected += 1;

            if (player.hotbar_selected == player.hotbar_entries) {
                player.hotbar_selected = 0;
            }
        }

        if (key_handler.isJustPressed(VK_UP)) {
            if (player.hotbar_selected == 0) {
                player.hotbar_selected = player.hotbar_entries;
            }

            player.hotbar_selected -= 1;
        }
    }

    void Hud::inventory_reset(GameState &game) {
        Player &player = game.getPlayer();

        inventory.entries.clear();

        const unsigned int inventory_size = player.inventory.size();
        for (unsigned int i = 0; i < inventory_size; ++i) {
            ItemStack &istack = player.inventory.get(i);

            inventory.entries.push_back({
                istack.getDef(),
                istack.getCount(),
            });
        }
    }

    void Hud::inventory_render(GameState &game, Display &d) {
        std::ostringstream oss;

        for (int i = 0; i < inventory.height; ++i) {
            int entry_i = inventory.selected - inventory.height / 2 + i;

            if (entry_i < 0 || entry_i >= static_cast<int>(inventory.entries.size())) {
                continue;
            }

            oss.str("");
            oss.clear();

            // "i: " means "inventory"
            oss<<"i: ";

            if (entry_i == static_cast<int>(inventory.selected)) {
                oss<<"> ";
            }

            InventoryEntry &entry = inventory.entries[entry_i];

            if (entry.isEmpty()) {
                oss<<"(none)";
            } else {
                oss<<entry.item_def->description;

                if (entry.count > 1) {
                    oss<<" (x"<<entry.count<<")";
                }
            }

            d.writeString(oss.str().c_str(), 1, inventory.y + i);
        }
    }

    void Hud::inventory_update(GameState &game) {
        Player &player = game.getPlayer();
        KeyHandler &key_handler = game.getKeyHandler();

        if (key_handler.isJustPressed(VK_DOWN)) {
            // If ctrl pressed, scroll down until non-empty item found
            if (key_handler.isPressed(VK_CONTROL)) {

                // FIXME - this code looks weird, i probably should change it
                if (inventory.selected != inventory.entries.size() - 1) {
                    while (inventory.selected++ < inventory.entries.size() - 2 &&
                           inventory.entries[inventory.selected].isEmpty()) {}
                }

            } else {
                inventory.selected += 1;

                if (inventory.selected == inventory.entries.size()) {
                    inventory.selected = 0;
                }
            }
        }

        if (key_handler.isJustPressed(VK_UP)) {
            // If ctrl pressed, scroll up until non-empty item found
            if (key_handler.isPressed(VK_CONTROL)) {

                // FIXME - Same as above
                if (inventory.selected != 0) {
                    while (inventory.selected-- != 0 && inventory.entries[inventory.selected].isEmpty()) {}
                }

            } else {
                if (inventory.selected == 0) {
                    inventory.selected = inventory.entries.size();
                }

                inventory.selected -= 1;
            }
        }

        if (key_handler.isJustPressed(VK_RETURN)) {
            player.hotbar[player.hotbar_selected] = inventory.entries[inventory.selected].item_def;
        }

        if (key_handler.isJustPressed(0x49)) {
            state = HudState::NONE;
        }
    }

}
