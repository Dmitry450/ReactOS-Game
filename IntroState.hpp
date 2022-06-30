#ifndef INTROSTATE_HPP_INCLUDED
#define INTROSTATE_HPP_INCLUDED

#include "State.hpp"

class IntroState : public State {

    static IntroState instance;

    int frameCount = 0;
    int maxFrames = 100;

    const char* message = "ReactOS Game!";

public:

    void cleanup() override;

    void handleKeyDown(WORD keyCode) override;
    void handleKeyUp(WORD keyCode) override;

    void update() override;
    void render(Game::Display& display) override;

    static IntroState* Instance() {
        return &instance;
    }

protected:
    IntroState() {}; // protected constructor for singleton

    void setup() override;
};

#endif // INTROSTATE_HPP_INCLUDED
