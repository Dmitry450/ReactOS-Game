#ifndef HITBOX_HPP_INCLUDED
#define HITBOX_HPP_INCLUDED

namespace Game {

    struct Hitbox {
        double x, y, w, h;

        Hitbox(double _x, double _y, double _w, double _h):
            x(_x), y(_y), w(_w), h(_h)
        {}

        inline double left() const { return x; }
        inline double right() const { return x + w; }

        inline double top() const { return y; }
        inline double bottom() const { return y + h; }

        inline bool collidePoint(double x, double y) const {
            return (x >= left() && x <= right() && y >= top() && y <= bottom());
        }

        inline bool collideHitbox(const Hitbox &other) const {
            if (right() < other.left() || other.right() < left()) {
                return false;
            }

            if (top() < other.bottom() || other.top() < bottom()) {
                return false;
            }

            return true;
        }
    };
}

#endif
