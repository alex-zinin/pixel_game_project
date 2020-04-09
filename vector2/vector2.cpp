#include"vector2.h"



//Vector2::Vector2(Vector2& v) {
//    this->x = v.x;
//    this->y = v.y;
//}


void Vector2::Norm(){
    this->x = this->x/Len();
    this->y = this->y/Len();
}


Vector2& Vector2::operator+(const Vector2& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

//Vector2& Vector2::operator=(Vector2& other){
//    this->x = other.x;
//    this->y = other.y;
//    return *this;
//}

Vector2& Vector2::operator-(const Vector2& other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}


float Vector2::operator*(const Vector2& other) const
{
    return this->x*other.x + this->y*other.y;
}

float Vector2::operator^(const Vector2& other) const
{
    return this->x*other.y - this->y*other.x;
}

Vector2& Vector2::operator*(int other)
{
    this->x *= other;
    this->y *= other;
    return *this;
}

Vector2& Vector2::operator/(int other)
{
    this->x /= other;
    this->y /= other;
    return *this;
}


float Vector2::SquareLen() const
{
    return x*x + y*y;
}

float Vector2::Len() const
{
    return sqrt(x*x + y*y);
}

Vector2 Vector2::operator-() const
{
    return {this->x -1, this->y -1};
}

Vector2& Vector2::rotate(int angle)
{
    this->x = this->x*cos(angle) + this->y*sin(angle);
    this->y = this->x*sin(angle) + this->y*cos(angle);
    return *this;
}



Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

float operator*(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

float operator^(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x*rhs.y - lhs.y*rhs.x;
}

Vector2 operator*(const Vector2& v, int other)
{
    return {v.x*other, v.y*other};
}


Vector2 operator*(int other, const Vector2& v)
{
    return {v.x*other, v.y*other};
}



std::istream& operator>>(std::istream& is, Vector2& vect)
{
    is >> vect.x >> vect.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Vector2& vect)
{
    os << "{" << vect.x << " " << vect.y << "}";
    return os;
}


Vector2 norm(const Vector2& v)
{
    return {v.x/v.Len(),v.y/v.Len()};
}


Vector2 Perp(const Vector2& v)
{
    return {-v.y, v.x};
}

Vector2 getRotated(const Vector2& v, int angle)
{
    return {v.x * cos(angle) + v.y * sin(angle), v.x *sin(angle) + v.y *cos(angle)};
}
