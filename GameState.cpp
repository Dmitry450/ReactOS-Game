#include "GameState.hpp"
#include "Tile.hpp"
#include "Color.hpp"
#include "ItemBlock.hpp"
#include <algorithm>
#include <math.h>
#include <sstream>

GameState GameState::instance;

void GameState::setup() {

    Game::Display& d = game->getDisplay();

    cam_offset.x = d.getWidth() / 2;
    cam_offset.y = d.getHeight() / 2;

    world.create();

    // load the player texture
    playerImg.load("player.txt");
    playerImg.setTransparency(Game::TRANSPARENT_BG);
    playerImg.setColor(Game::FG_LIGHT_YELLOW);

    block_defs.load("block_defs.txt");

    std::shared_ptr<Game::ItemDef> grass_item_def = std::make_shared<Game::ItemDef>();
    grass_item_def->name = "default:grass";
    grass_item_def->description = "Grass block";
    grass_item_def->controller = std::unique_ptr<Game::ItemController>(new Game::ItemBlock(1));

    item_defs.registerItem(grass_item_def);

    Game::ItemStack grass_istack;
    grass_istack.set(grass_item_def, 10);

    player.inventory.addItem(grass_istack);

    player.hotbar[0] = grass_item_def;

    Game::PlayerEntity *player_entity = new Game::PlayerEntity(
        Game::Hitbox(World::SIZE/2 * TILE_WIDTH, World::SIZE/2 * TILE_HEIGHT - 4, 4, 4)
    );

    player_entity->loadSprite("resources/entities/player.sprite");

    std::unique_ptr<Game::Entity> player_entity_ptr(player_entity);

    entity_mgr.addEntity(std::move(player_entity_ptr));

    player_entity->assignPlayer(&player);
}

void GameState::cleanup() {

}

void GameState::handleKeyDown(WORD keyCode) {
    key_handler.press(keyCode);

}

void GameState::handleKeyUp(WORD keyCode) {
    key_handler.release(keyCode);
}

void GameState::handleMouseEvent(MOUSE_EVENT_RECORD* event) {
    player.mouse.x = event->dwMousePosition.X - cam_offset.x;
    player.mouse.y = event->dwMousePosition.Y - cam_offset.y;

    player.lmb = event->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED;
    player.rmb = event->dwButtonState & RIGHTMOST_BUTTON_PRESSED;
}

void GameState::update() {
    hud.update(*this);

    if (key_handler.isPressed(0x51)) {
        game->quit();
    }

    player.down = key_handler.isPressed(0x53);
    player.left = key_handler.isPressed(0x41);
    player.right = key_handler.isPressed(0x44);
    player.jump = key_handler.isPressed(VK_SPACE);

    entity_mgr.update(*this);

    Game::Entity *player_entity = player.getEntity(*this);

    if (player_entity != nullptr) {
        cam.x = static_cast<int>(player_entity->hitbox.x);
        cam.y = static_cast<int>(player_entity->hitbox.y);
    }

    key_handler.update();
}

void GameState::render(Game::Display& display) {
    display.setColor(Game::BG_AQUA | Game::FG_LIGHT_YELLOW);
    display.clear(' ');

    auto blocks = block_defs.getAtlas().getTexture();

    int start_x = (cam.x-cam_offset.x)/TILE_WIDTH;
    int end_x = start_x + game->getDisplay().getWidth()/TILE_WIDTH + 1;

    int start_y = (cam.y-cam_offset.y)/TILE_HEIGHT;
    int end_y = start_y + game->getDisplay().getHeight()/TILE_HEIGHT + 1;

    for (int x = start_x; x <= end_x; x++) {
        for (int y = start_y; y <= end_y; y++) {
            int block = world.get(x, y);

            if (block != 0) {
                Game::BlockDef &def = block_defs.getDef(block);
                blocks.setColor(def.color);

                blocks.render(display, x*TILE_WIDTH - (cam.x-cam_offset.x), y*TILE_HEIGHT - (cam.y-cam_offset.y), &def.texture_rect);
            }
        }
    }

    // TODO - move this into HUD
    int mouseBlockX = player.mouse.x + cam_offset.x - (player.mouse.x+2*cam_offset.y+cam.x)%TILE_WIDTH;
    int mouseBlockY = player.mouse.y + cam_offset.y - (player.mouse.y+2*cam_offset.y+cam.y)%TILE_HEIGHT;
    display.setTransparency(Game::TRANSPARENT_BG);

    display.setColor(Game::FG_WHITE);
    display.setChar(0xC9, mouseBlockX, mouseBlockY);
    display.drawLine(0xCD, mouseBlockX + 1, mouseBlockY, mouseBlockX + TILE_WIDTH - 2, mouseBlockY);
    display.setChar(0xBB, mouseBlockX + TILE_WIDTH - 1, mouseBlockY);
    display.drawLine(0xBA, mouseBlockX, mouseBlockY + 1, mouseBlockX, mouseBlockY + TILE_HEIGHT - 2);
    display.setChar(0xC8, mouseBlockX, mouseBlockY + TILE_HEIGHT - 1);
    display.drawLine(0xCD, mouseBlockX + 1, mouseBlockY + TILE_HEIGHT - 1, mouseBlockX + TILE_WIDTH - 2, mouseBlockY + TILE_HEIGHT - 1);
    display.setChar(0xBC, mouseBlockX + TILE_WIDTH - 1, mouseBlockY + TILE_HEIGHT - 1);
    display.drawLine(0xBA, mouseBlockX + TILE_WIDTH - 1, mouseBlockY + TILE_HEIGHT - 2, mouseBlockX + TILE_WIDTH - 1, mouseBlockY + 1);

    entity_mgr.render(display, cam-cam_offset);

    hud.render(*this, display);

}
