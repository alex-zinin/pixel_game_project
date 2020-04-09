#pragma once

#include<cmath>
#include<iostream>



class Vector2
{
public:
    Vector2(): x(0), y(0) {}
    //Vector2(Vector2& v);
    Vector2(double a, double b): x(a), y(b) {}
    Vector2& operator+(const Vector2& other);
    Vector2& operator-(const Vector2& other);
    float operator*(const Vector2& other) const;
    float operator^(const Vector2& other) const;
    Vector2& operator*(int other);
    Vector2& operator/(int other);
   // Vector2& operator=(Vector2& other);
    float SquareLen() const;
    float Len() const;
    void Norm();
    Vector2 operator-() const;
    Vector2& rotate(int angle);
    ~Vector2()
    {
        x = 0;
        y = 0;
    }

public:
    double x, y;
};



Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
float operator*(const Vector2& lhs, const Vector2& rhs);
float operator^(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& v, int other);
Vector2 operator*(int other, const Vector2& v);
std::istream& operator>>(std::istream& is, Vector2& vect);
std::ostream& operator<<(std::ostream& os, const Vector2& vect);
Vector2 norm(const Vector2& v);
Vector2 Perp(const Vector2& v);
Vector2 getRotated(const Vector2& v, int angle);
