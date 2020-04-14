#pragma once

#include <ostream>
#include <cmath>

struct vec3 {
    union{double x, r;};
    union{double y, g;};
    union{double z, b;};
    
    vec3 operator-() const { 
        return vec3{
            -this->x,
            -this->y,
            -this->z
        }; 
    }

    vec3& operator+=(const vec3 &v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    vec3& operator*=(const double t) {
        this->x *= t;
        this->y *= t;
        this->z *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return 
            this->x * this->x +
            this->y * this->y +
            this->z * this->z;
    }

    void write_color(std::ostream &out) {
        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(255.999 * this->x) << ' '
            << static_cast<int>(255.999 * this->y) << ' '
            << static_cast<int>(255.999 * this->z) << '\n';
    }
};


inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3{u.x + v.x, u.y + v.y, u.z + v.z};
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3{u.x - v.x, u.y - v.y, u.z - v.z};
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3{u.x * v.x, u.y * v.y, u.z * v.z};
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3{t * v.x, t * v.y, t * v.z};
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.x * v.x
         + u.y * v.y
         + u.z * v.z;
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3{
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}
