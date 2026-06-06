#ifndef VEC_HPP
#define VEC_HPP

#include <cmath>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

template<typename T, int N>
class Vec
{
public:
    Vec() = default;

    Vec(std::initializer_list<T> list);  

    // Mathematical Operators
    inline Vec<T, N> operator+(const Vec<T, N>& other) const;
    inline Vec<T, N> operator-(const Vec<T, N>& other) const;
    inline Vec<T, N> operator*(const Vec<T, N>& other) const;
    inline Vec<T, N> operator/(const Vec<T, N>& other) const;
    inline Vec<T, N> operator*(T scalar) const;
    inline Vec<T, N> operator/(T scalar) const;
    inline Vec<T, N>& operator+=(const Vec<T, N>& other);
    inline Vec<T, N>& operator-=(const Vec<T, N>& other);
    inline Vec<T, N>& operator*=(const Vec<T, N>& other);
    inline Vec<T, N>& operator/=(const Vec<T, N>& other);
    inline Vec<T, N>& operator*=(T scalar);
    inline Vec<T, N>& operator/=(T scalar);

    double length() const;
    double dot(const Vec<T, N>& other) const;
    Vec<T, N> normalized() const;


    T  at(int i) const;
    T& at(int i);
    T& operator[](int i);
    const T& operator[](int i) const;
    T& x();
    T& y();

   const T& x() const;
   const T& y() const;

private:
    T data[N]{};
};

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<int, 2> Vec2i;

#include "Vec.tpp"

#endif // !VEC_HPP
