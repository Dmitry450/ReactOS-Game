#ifndef TRANSPARENCY_HPP_INCLUDED
#define TRANSPARENCY_HPP_INCLUDED

#include <map>
#include <string>

namespace Game {

    enum Transparency {
        TRANSPARENT_BG,
        TRANSPARENT_FG,
        TRANSPARENT_NO
    };

    static const std::map<std::string, Transparency> TRANSPARENCY_MAP = {
        { "background", Transparency::TRANSPARENT_BG },
        { "foreground", Transparency::TRANSPARENT_FG },
        { "no",         Transparency::TRANSPARENT_NO },
    };

}

#endif // TRANSPARENCY_HPP_INCLUDED
