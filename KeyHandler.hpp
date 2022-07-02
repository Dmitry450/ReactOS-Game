#ifndef KEY_HANDLER_HPP_INCLUDED
#define KEY_HANDLER_HPP_INCLUDED

#include <unordered_map>

#include <windows.h>


namespace Game {

    class KeyHandler {
        // Probably not the best way
        std::unordered_map<WORD, bool> keys_pressed;
        std::unordered_map<WORD, bool> keys_just_pressed;

        std::unordered_map<WORD, bool> keys_released;

    public:
        inline void update() {
            keys_released.clear();
            keys_just_pressed.clear();
        }

        inline void press(WORD key) {
            keys_just_pressed[key] = !isPressed(key);
            keys_pressed[key] = true;
        }

        inline void release(WORD key) {
            if (isPressed(key)) {
                keys_released[key] = true;
            }

            keys_pressed[key] = false;
        }

        inline bool isPressed(WORD key) {
            auto pair = keys_pressed.find(key);

            if (pair != keys_pressed.end()) {
                return pair->second;
            }

            return false;
        }

        inline bool isReleased(WORD key) {
            auto pair = keys_released.find(key);

            if (pair != keys_released.end()) {
                return pair->second;
            }

            return !isPressed(key);
        }

        inline bool isJustPressed(WORD key) {
            auto pair = keys_just_pressed.find(key);

            if (pair != keys_just_pressed.end()) {
                return pair->second;
            }

            return false;
        }

        inline bool isJustReleased(WORD key) {
            // If key was released this frame, keys_pressed WILL have key
            // with value "false". If key is pressed, this will return false.
            // If key not found, this means key was never pressed, neither released
            auto pair = keys_pressed.find(key);

            if (pair != keys_pressed.end()) {
                return !pair->second;
            }

            return false;
        }
    };

}

#endif
