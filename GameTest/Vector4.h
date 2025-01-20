#pragma once
#include "stdafx.h"
class Vector4
{
public:
    Vector4() {};
    Vector4(float nx, float ny, float nz, float nw) : x(nx), y(ny), z(nz), w(nw) {};

    void operator=(const Vector4& other) { x = other.x; y = other.y; z = other.z; w = other.w; };

    // addition
    Vector4 operator+(const Vector4& other) { return Vector4(x + other.x, y + other.y, z + other.z, w + other.w); };
    void operator+=(const Vector4& other) { x += other.x, y += other.y; z += other.z; w += other.w; };
    void operator+=(const float& other) { x += other, y += other; z += other; w += other;};

    // subtraction
    Vector4 operator-(const Vector4& other) { return Vector4(x - other.x, y - other.y, z - other.z, w - other.z); };
    void operator-=(const Vector4& other) { x -= other.x, y -= other.y; z -= other.z; w -= other.w; };
    void operator-=(const float& other) { x -= other; y -= other; z -= other; w -= other; };

    // multiplication
    Vector4 operator*(const float& other) { return Vector4(x * other, y * other, z * other, w * other); };
    void operator*=(const float& other) { x *= other, y *= other; z *= other; w *= other;};

    // division
    Vector4 operator/(const float& other) { return Vector4(x / other, y / other, z / other, w / other); };
    void operator/=(const float& other) { x /= other, y /= other; z /= other; w /= other;};

    //magnitude
    float LengthSquared() const { return x * x + y * y + z * z + w * w; };
    float Length() const { return sqrtf(LengthSquared()); };

    void Normalize() { float len = Length(); x /= len; y /= len; z /= len; w /= len; };
    Vector4 Normalized() const { float len = Length(); return Vector4(x / len, y / len, z / len, w / len); };

    float Dot(const Vector4& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; };
    //float Dot(const Vector4& other) const { return x * other.x + y * other.y; };

    float Distance(const Vector4& other) { return (*this - other).Length(); };
    float DistanceSquared(const Vector4& other) { return (*this - other).LengthSquared(); };

    Vector4 Max(const Vector4& other) { return Vector4(fmaxf(x, other.x), fmaxf(y, other.y), fmaxf(z, other.z), fmaxf(w, other.w)); };
    Vector4 Min(const Vector4& other) { return Vector4(fminf(x, other.x), fminf(y, other.y), fminf(z, other.z), fminf(w, other.w)); };

    //Vector4 Perpendicular() { return Vector4(-y, x); };

    //bool operators :D
    bool operator>= (const Vector4& other) { return x >= other.x && y >= other.y && z >= other.z && w >= other.w; };
    bool operator<= (const Vector4& other) { return x <= other.x && y <= other.y && z <= other.z && w <= other.w; };
    bool operator> (const Vector4& other) { return x > other.x && y > other.y && z > other.z && w > other.w;};
    bool operator< (const Vector4& other) { return x < other.x && y < other.y && z < other.z && w < other.w;; };
    bool operator== (const Vector4& other) { return x == other.x && y == other.y && z == other.z && w == other.w;; };
    bool operator!= (const Vector4& other) { return x != other.x || y != other.y || z != other.z || w != other.w;; };
    bool operator!() { return x == NULL && y == NULL && z == NULL && w == NULL; };
    Vector4 operator-() { return Vector4(-x, -y, -z, -w); };

    void Set(float nx, float ny, float nz, float nw) { x = nx; y = ny; z = nz; w = nw; };



    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;
};
