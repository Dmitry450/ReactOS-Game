#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "State.hpp"
#include "Texture.hpp"
#include "World.hpp"
#include "Tile.hpp"
#include "EntityManager.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include "Hitbox.hpp"
#include <vector>

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

    int camX, camY;

public:

    void cleanup();

    void handleKeyDown(WORD keyCode);
    void handleKeyUp(WORD keyCode);
    void handleMouseEvent(MOUSE_EVENT_RECORD* event);

    void update();
    void render(Game::Display& display);

    static GameState* Instance() {
        return &instance;
    }

    inline World &getWorld() { return world; }
    inline Game::BlockDefManager &getBlockDefs() { return block_defs; }
    inline Game::EntityManager &getEntityManager() { return entity_mgr; }

protected:
    GameState() {}; // protected constructor for singleton

    void setup();
};

#endif // GAMESTATE_HPP_INCLUDED
