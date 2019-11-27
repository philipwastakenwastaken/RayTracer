#pragma once

#include <math.h>
#include <iostream>

namespace trace {


    struct vec3 {

        vec3() = default;
        vec3(float x, float y, float z): x(x), y(y), z(z) {}
        vec3(float x): x(x), y(x), z(x) {}

        float x, y, z;


        
        inline const vec3& operator+() const { return *this; }
        inline vec3 operator-() const { return vec3(-x, -y, -z); }

        inline vec3& operator+=(const vec3 &v2);
        inline vec3& operator-=(const vec3 &v2);
        inline vec3& operator*=(const vec3 &v2);
        inline vec3& operator/=(const vec3 &v2);
        inline vec3& operator*=(const float t);
        inline vec3& operator/=(const float t);

        inline float length() const { return sqrt(x * x + y * y + z * z); }
        inline float squared_length() const { return x * x + y * y + z * z; }
        inline void make_unit_vector();

    };


    inline vec3& vec3::operator+=(const vec3 &v2) {
        x = x + v2.x;
        y = y + v2.y;
        z = z + v2.z;
        return *this;
    }

    inline vec3& vec3::operator-=(const vec3 &v2) {
        x = x - v2.x;
        y = y - v2.y;
        z = z - v2.z;
        return *this;
    }

    inline vec3& vec3::operator*=(float t) {
        x = x * t;
        y = y * t;
        z = z * t;
        return *this;
    }


    inline vec3& vec3::operator/=(float t) {
        x = x * t;
        y = y * t;
        z = z * t;
        return *this;
    }

    inline vec3 operator/(vec3 v, float scalar) {
        return vec3(v.x / scalar, v.y / scalar, v.z / scalar);
    }

    inline vec3 operator*(const vec3& v1, const vec3& v2) {
        return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    inline vec3 operator*(const vec3& v, float scalar) {
        return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    inline vec3 operator*(float scalar, const vec3& v) {
        return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    inline vec3 operator+(const vec3& v1, const vec3& v2) {
        return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    inline vec3 operator-(const vec3& v1, const vec3& v2) {
        return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    inline float dot(const vec3& v1, const vec3& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    inline vec3 cross(const vec3& v1, const vec3& v2) {
        return vec3(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
    }

    inline vec3 normalize(vec3 v) {
        return v / v.length();
    }

    inline std::istream& operator>>(std::istream& is, vec3& t) {
        is >> t.x >> t.y >> t.z;
        return is;
    }

    inline std::ostream& operator<<(std::ostream& os, const vec3& t) {
        os << t.x << " " << t.y << " " << t.z;
        return os;
    }

}