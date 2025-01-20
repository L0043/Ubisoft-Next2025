#pragma once
#include "stdafx.h"
#include <corecrt_math.h>
class Vector2
{
public:
    Vector2() {};
    Vector2(float nx, float ny) : x(nx), y(ny) {};
    
    void operator=(const Vector2& other) { x = other.x; y = other.y; };
  //void operator=(const Vector4& other) { x = other.x; y = other.y; z = other.z; w = other.w; };
    // addition
    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); };
    Vector2 operator+(const float& other) const { return Vector2(x + other, y + other); };
    void operator+=(const Vector2& other) { x += other.x, y += other.y; };
    void operator+=(const float& other) { x += other, y += other; };

    // subtraction
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); };
    Vector2 operator-(const float& other) const { return Vector2(x - other, y - other); };
    void operator-=(const Vector2& other) { x -= other.x, y -= other.y; };

    // multiplication
    Vector2 operator*(const float& other) const { return Vector2(x * other, y * other); };
    Vector2 operator*(const Vector2& other) const { return Vector2(x * other.x, y * other.y); };
    void operator*=(const float& other) { x *= other, y *= other; };
    void operator*=(const Vector2& other) { x *= other.x, y *= other.y; };
    friend Vector2 operator*(const float& scalar, const Vector2& vector) { return Vector2(vector.x * scalar, vector.y * scalar); };

    // division
    Vector2 operator/(const float& other) const { return Vector2(x / other, y / other); };
    Vector2 operator/(const Vector2& other) const { return Vector2(x / other.x, y / other.y); };
    void operator/=(const float& other) { x /= other, y /= other; };

    //magnitude
    float LengthSquared() const { return x * x + y * y; };
    float Length() const { return sqrtf(LengthSquared()); };

    void Normalize() { float len = Length(); x /= len; y /= len; };
    Vector2 Normalized() const { float len = Length(); return Vector2(x / len, y / len); };

    float Dot(const Vector2& other) const { return x * other.x + y * other.y; };
    //Vector2 Cross(const Vector2& other){ return }

    float Distance(const Vector2& other) { return (*this - other).Length(); };
    float DistanceSquared(const Vector2& other) { return (*this - other).LengthSquared(); };

    Vector2 Max(const Vector2& other) { return Vector2(fmaxf(x, other.x), fmaxf(y, other.y)); };
    Vector2 Max(const Vector2& other) const { return Vector2(fmaxf(x, other.x), fmaxf(y, other.y)); };
    Vector2 Min(const Vector2& other) { return Vector2(fminf(x, other.x), fminf(y, other.y)); };

    Vector2 Perpendicular() { return Vector2(-y, x); };

    //bool operators :D
    bool operator>= (const Vector2& other) { return x >= other.x && y >= other.y; };
    bool operator<= (const Vector2& other) { return x <= other.x && y <= other.y; };
    bool operator> (const Vector2& other) { return x > other.x && y > other.y; };
    bool operator< (const Vector2& other) { return x < other.x && y < other.y; };
    bool operator== (const Vector2& other) { return x == other.x && y == other.y; };
    bool operator!= (const Vector2& other) { return x != other.x || y != other.y; };
    bool operator!() { return x == NULL && y == NULL; };
    Vector2 operator-() { return Vector2(-x, -y); };

    void Set(float nx, float ny) { x = nx; y = ny; };
    bool Clamp(const float& limit) { return this->Length() > limit; }

    float x = 0;
    float y = 0;

    static Vector2 Zero() { return Vector2(0, 0); };
    static Vector2 One() { return Vector2(1, 1); };
};