#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include <vector>

#include "State.hpp"
#include "Texture.hpp"
#include "World.hpp"
#include "Tile.hpp"
#include "EntityManager.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include "Hitbox.hpp"
#include "KeyHandler.hpp"
#include "Hud.hpp"
#include "Vector.hpp"

enum GameDirection {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

class GameState : public State {

    static GameState instance;

    World world;
    Game::BlockDefManager block_defs;
    Game::ItemDefManager item_defs;
    Game::EntityManager entity_mgr;

    Game::Player player = Game::Player(1.0, 0.125, 1.0);

    std::vector<Game::Rect> frames = {
        {0, 0, 4, 5},
        {0, 5, 4, 5},
        {0, 10, 4, 5},
        {0, 15, 4, 5},
        {0, 20, 4, 5},
        {0, 25, 4, 5}
    };
    int currentFrame = 0;

    Game::Texture playerImg;

    Game::Vector2i cam = { 0, 0 };
    Game::Vector2i cam_offset = { 0, 0 };

    Game::KeyHandler key_handler;
    Game::Hud hud;

public:

    void cleanup() override;

    void handleKeyDown(WORD keyCode) override;
    void handleKeyUp(WORD keyCode) override;
    void handleMouseEvent(MOUSE_EVENT_RECORD* event) override;

    void update() override;
    void render(Game::Display& display) override;

    static GameState* Instance() {
        return &instance;
    }

    inline World &getWorld() { return world; }
    inline Game::BlockDefManager &getBlockDefs() { return block_defs; }
    inline Game::EntityManager &getEntityManager() { return entity_mgr; }
    inline Game::Player &getPlayer() { return player; }
    inline Game::KeyHandler &getKeyHandler() { return key_handler; }
    inline Game::Vector2i &getCamera() { return cam; }

protected:
    GameState() {}; // protected constructor for singleton

    void setup() override;
};

#endif // GAMESTATE_HPP_INCLUDED
