// Constructor
template<typename T, int N>
Vec<T, N>::Vec(std::initializer_list<T> list)
{
    assert(list.size() == N);
    std::copy(list.begin(), list.end(), data);
}

template<typename T, int N>
inline Vec<T, N> Vec<T, N>::operator+(const Vec<T, N>& other) const
{
    Vec<T, N> result;
    for (int i = 0; i < N; ++i)
    {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

template<typename T, int N>
inline Vec<T, N> Vec<T, N>::operator-(const Vec<T, N>& other) const
{
    Vec<T, N> result;
    for (int i = 0; i < N; ++i)
    {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

template<typename T, int N>
inline Vec<T, N> Vec<T, N>::operator*(const Vec<T, N>& other) const
{
    Vec<T, N> result;
    for (int i = 0; i < N; ++i)
    {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}

template<typename T, int N>
inline Vec<T, N> Vec<T, N>::operator/(const Vec<T, N>& other) const
{
    Vec<T, N> result;
    for (int i = 0; i < N; ++i)
    {
        if (other.data[i] == 0)
        {
            throw std::runtime_error("Division by zero in Vec operator/");
        }
        result.data[i] = data[i] / other.data[i];
    }
    return result;
}

template<typename T, int N>
inline Vec<T, N>& Vec<T, N>::operator+=(const Vec<T, N>& other) 
{
    for (int i = 0; i < N; ++i)
    {
        data[i] += other.data[i];
    }
    return *this;
}

template<typename T, int N>
inline Vec<T, N>& Vec<T, N>::operator-=(const Vec<T, N>& other) 
{
    for (int i = 0; i < N; ++i)
    {
        data[i] -= other.data[i];
    }
    return *this;
}

template<typename T, int N>
inline Vec<T, N>& Vec<T, N>::operator*=(const Vec<T, N>& other) 
{
    for (int i = 0; i < N; ++i)
    {
        data[i] *= other.data[i];
    }
    return *this;
}


template<typename T, int N>
inline Vec<T, N>& Vec<T, N>::operator/=(const Vec<T, N>& other) 
{
    for (int i = 0; i < N; ++i)
    {
        if (other.data[i] == 0)
        {
            throw std::runtime_error("Division by zero in Vec operator/=");
        }
        data[i] /= other.data[i];
    }
    return *this;
}

template<typename T, int N>
inline Vec<T, N> Vec<T, N>::operator*(T scalar) const
{
    Vec<T, N> result;
    for (int i = 0; i < N; ++i)
    {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

template<typename T, int N>
inline Vec<T, N> Vec<T, N>::operator/(T scalar) const
{
    if (scalar == T(0))
    {
        throw std::runtime_error("Division by zero in Vec operator/");
    }
    Vec<T, N> result;
    for (int i = 0; i < N; ++i)
    {
        result.data[i] = data[i] / scalar;
    }
    return result;
}

template<typename T, int N>
inline Vec<T, N>& Vec<T, N>::operator*=(T scalar)
{
    for (int i = 0; i < N; ++i)
    {
        data[i] *= scalar;
    }
    return *this;
}

template<typename T, int N>
inline Vec<T, N>& Vec<T, N>::operator/=(T scalar)
{
    if (scalar == T(0))
    {
        throw std::runtime_error("Division by zero in Vec operator/=");
    }
    for (int i = 0; i < N; ++i)
    {
        data[i] /= scalar;
    }
    return *this;
}

template<typename T, int N>
double Vec<T, N>::length() const
{
    double sum = 0.0;
    for (int i = 0; i < N; ++i)
    {
        sum += static_cast<double>(data[i]) * static_cast<double>(data[i]);
    }
    return std::sqrt(sum);
}

template<typename T, int N>
double Vec<T, N>::dot(const Vec<T, N>& other) const
{
    double result = 0.0;
    for (int i = 0; i < N; ++i)
    {
        result += static_cast<double>(data[i]) * static_cast<double>(other.data[i]);
    }
    return result;
}

template<typename T, int N>
Vec<T, N> Vec<T, N>::normalized() const
{
    double len = length();
    if (len == 0)
    {
        throw std::runtime_error("Cannot normalize a zero-length vector");
    }
    Vec<T, N> result;
    for (int i = 0; i < N; ++i)
    {
        result.data[i] = data[i] / len;
    }
    return result;
}


template<typename T, int N>
T Vec<T, N>::at(int i) const
{
        assert(i >= 0 && i < N);
        return data[i];
}

template<typename T, int N>
T& Vec<T, N>::at(int i)
{   
    assert(i >= 0 && i < N);
    return data[i];
}

template<typename T, int N>
T& Vec<T, N>::operator[](int i)
{
    return data[i];
}

template<typename T, int N>
const T& Vec<T, N>::operator[](int i) const
{
    return data[i];
}

template<typename T,int N>
T& Vec<T,N>::x()
{
    static_assert(N >= 1);
    return data[0];
}

template<typename T,int N>
T& Vec<T,N>::y()
{
    static_assert(N >= 2);
    return data[1];
}

template<typename T,int N>
const T& Vec<T,N>::x() const
{
    static_assert(N >= 1);
    return data[0];
}

template<typename T,int N>
const T& Vec<T,N>::y() const
{
    static_assert(N >= 2);
    return data[1];
}