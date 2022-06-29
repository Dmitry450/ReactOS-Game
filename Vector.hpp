#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

#include <cmath>

namespace Game {

    template<class T>
    struct Vector {
        T x, y;

        inline Vector operator+(const Vector &other) const {
            return { x + other.x, y + other.y };
        }

        inline void operator+=(const Vector &other) {
            x += other.x;
            y += other.y;
        }

        inline Vector operator-(const Vector &other) const {
            return { x - other.x, y - other.y };
        }

        inline void operator-=(const Vector &other) {
            x -= other.x;
            y -= other.y;
        }

        inline Vector operator*(double num) const {
            return { x * num, y * num };
        }

        inline void operator*=(double num) {
            x *= num;
            y *= num;
        }

        inline Vector operator/(double num) const {
            return { x/num, y/num };
        }

        inline void operator/=(double num) {
            x /= num;
            y /= num;
        }

        inline T length() {
            return sqrt(x*x + y*y);
        }
    };

    typedef Vector<double> Vector2d;
    typedef Vector<int> Vector2i;
}

#endif
