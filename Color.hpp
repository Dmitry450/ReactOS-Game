#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include <map>
#include <string>

namespace Game {

    enum Color {
        FG_BLACK        = 0x00,
        FG_GRAY         = 0x08,
        FG_LIGHT_GRAY   = 0x07,
        FG_WHITE        = 0x0F,
        FG_BLUE         = 0x01,
        FG_LIGHT_BLUE   = 0x09,
        FG_GREEN        = 0x02,
        FG_LIGHT_GREEN  = 0x0A,
        FG_AQUA         = 0x03,
        FG_LIGHT_AQUA   = 0x0B,
        FG_RED          = 0x04,
        FG_LIGHT_RED    = 0x0C,
        FG_PURPLE       = 0x05,
        FG_LIGHT_PURPLE = 0x0D,
        FG_YELLOW       = 0x06,
        FG_LIGHT_YELLOW = 0x0E,


        BG_BLACK        = 0x00,
        BG_GRAY         = 0x80,
        BG_LIGHT_GRAY   = 0x70,
        BG_WHITE        = 0xF0,
        BG_BLUE         = 0x10,
        BG_LIGHT_BLUE   = 0x90,
        BG_GREEN        = 0x20,
        BG_LIGHT_GREEN  = 0xA0,
        BG_AQUA         = 0x30,
        BG_LIGHT_AQUA   = 0xB0,
        BG_RED          = 0x40,
        BG_LIGHT_RED    = 0xC0,
        BG_PURPLE       = 0x50,
        BG_LIGHT_PURPLE = 0xD0,
        BG_YELLOW       = 0x60,
        BG_LIGHT_YELLOW = 0xE0,
    };

    static const std::map<std::string, Color> FG_COLOR_MAP = {
        { "black",        Color::FG_BLACK },
        { "gray",         Color::FG_GRAY },
        { "light_gray",   Color::FG_LIGHT_GRAY },
        { "white",        Color::FG_WHITE },
        { "blue",         Color::FG_BLUE },
        { "light_blue",   Color::FG_LIGHT_BLUE },
        { "green",        Color::FG_GREEN },
        { "light_green",  Color::FG_LIGHT_GREEN },
        { "aqua",         Color::FG_AQUA },
        { "light_aqua",   Color::FG_LIGHT_AQUA },
        { "red",          Color::FG_RED },
        { "light_red",    Color::FG_LIGHT_RED },
        { "purple",       Color::FG_PURPLE },
        { "light_purple", Color::FG_LIGHT_PURPLE },
        { "yellow",       Color::FG_YELLOW },
        { "light_yellow", Color::FG_LIGHT_YELLOW },
    };

    static const std::map<std::string, Color> BG_COLOR_MAP = {
        { "black",        Color::BG_BLACK },
        { "gray",         Color::BG_GRAY },
        { "light_gray",   Color::BG_LIGHT_GRAY },
        { "white",        Color::BG_WHITE },
        { "blue",         Color::BG_BLUE },
        { "light_blue",   Color::BG_LIGHT_BLUE },
        { "green",        Color::BG_GREEN },
        { "light_green",  Color::BG_LIGHT_GREEN },
        { "aqua",         Color::BG_AQUA },
        { "light_aqua",   Color::BG_LIGHT_AQUA },
        { "red",          Color::BG_RED },
        { "light_red",    Color::BG_LIGHT_RED },
        { "purple",       Color::BG_PURPLE },
        { "light_purple", Color::BG_LIGHT_PURPLE },
        { "yellow",       Color::BG_YELLOW },
        { "light_yellow", Color::BG_LIGHT_YELLOW },
    };

}

#endif // COLOR_HPP_INCLUDED
