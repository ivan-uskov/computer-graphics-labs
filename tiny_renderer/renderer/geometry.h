#pragma once
#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

template<size_t DimCols, size_t DimRows, typename T>
class mat;

template <size_t DIM, typename T>
struct vec
{
    vec()
    { 
        for (size_t i = DIM; i--; data_[i] = T());
    }

    T & operator [] (size_t const i)
    {
        assert(i < DIM);
        return data_[i];
    }

     T const& operator [] (size_t const i) const
     {
         assert(i < DIM);
         return data_[i];
     }

private:
    T data_[DIM];
};

/////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct vec<2, T>
{
    vec()
        : x(T())
        , y(T())
    {}

    vec(T X, T Y)
        : x(X)
        , y(Y) 
    {}

    template <class U>
    vec<2,T>(vec<2, U> const& v);

    T & operator [] (size_t const i)
    {
        assert(i < 2);
        return i <= 0 ? x : y;
    }

    T const& operator [] (size_t const i) const
    {
        assert(i < 2);
        return i <= 0 ? x : y;
    }

    T x, y;
};

/////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct vec<3, T>
{
    vec()
        : x(T())
        , y(T())
        , z(T())
    {}

    vec(T X, T Y, T Z)
        : x(X)
        , y(Y)
        , z(Z)
    {}

    template <class U>
    vec<3,T>(const vec<3,U> &v);

    T & operator [] (size_t const i)
    {
        assert(i < 3);
        return i <= 0 ? x : (i == 1 ? y : z);
    }

    T const& operator [] (size_t const i) const
    {
        assert(i < 3);
        return i <= 0 ? x : (i == 1 ? y : z);
    }

    float norm()
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    vec<3,T> & normalize(T l = 1)
    {
        *this = (*this) * (l / norm());
        return *this;
    }

    T x, y, z;
};

/////////////////////////////////////////////////////////////////////////////////

template<size_t DIM, typename T>
T operator * (vec<DIM,T> const& lhs, vec<DIM,T> const& rhs)
{
    T ret = T();
    size_t i = DIM;
    while (i--)
    {
        ret += lhs[i] * rhs[i];
    }

    return ret;
}

template<size_t DIM, typename T>
vec<DIM,T> operator + (vec<DIM,T> lhs, vec<DIM,T> const& rhs)
{
    size_t i = DIM;
    while (i--)
    {
        lhs[i] += rhs[i];
    }

    return lhs;
}

template<size_t DIM, typename T>
vec<DIM, T> operator - (vec<DIM,T> lhs, vec<DIM,T> const& rhs)
{
    size_t i = DIM;
    while (i--)
    {
        lhs[i] -= rhs[i];
    }

    return lhs;
}

template<size_t DIM, typename T, typename U>
vec<DIM, T> operator * (vec<DIM,T> lhs, U const& rhs)
{
    size_t i = DIM;
    while (i--)
    {
        lhs[i] *= rhs;
    }

    return lhs;
}

template<size_t DIM, typename T, typename U>
vec<DIM, T> operator / (vec<DIM, T> lhs, U const& rhs)
{
    size_t i = DIM;
    while (i--)
    {
        lhs[i] /= rhs;
    }

    return lhs;
}

template<size_t LEN, size_t DIM, typename T>
vec<LEN, T> embed(vec<DIM, T> const& v, T fill = 1)
{
    vec<LEN, T> ret;
    size_t i = LEN;
    while (i--)
    {
        ret[i] = (i < DIM ? v[i] : fill);
    }

    return ret;
}

template<size_t LEN, size_t DIM, typename T>
vec<LEN, T> proj(vec<DIM, T> const& v)
{
    vec<LEN, T> ret;
    size_t i = LEN;
    while (i--)
    {
        ret[i] = v[i];
    }

    return ret;
}

template <typename T>
vec<3, T> cross(vec<3, T> v1, vec<3, T> v2)
{
    auto x = v1.y * v2.z - v1.z * v2.y;
    auto y = v1.z * v2.x - v1.x * v2.z;
    auto z = v1.x * v2.y - v1.y * v2.x;

    return vec<3, T>(x, y, z);
}

template <size_t DIM, typename T>
std::ostream & operator << (std::ostream & out, vec<DIM, T> & v)
{
    for(unsigned int i = 0; i < DIM; ++i)
    {
        out << v[i] << " ";
    }

    return out ;
}

/////////////////////////////////////////////////////////////////////////////////

template<size_t DIM, typename T>
struct dt
{
    static T det(mat<DIM, DIM, T> const& src)
    {
        T ret = 0;
        size_t i = DIM;
        while (i--)
        {
            ret += src[0][i] * src.cofactor(0, i);
        }

        return ret;
    }
};

template<typename T>
struct dt<1, T>
{
    static T det(mat<1, 1, T> const& src)
    {
        return src[0][0];
    }
};

/////////////////////////////////////////////////////////////////////////////////

template<size_t DimRows, size_t DimCols, typename T>
class mat
{
    vec<DimCols, T> rows[DimRows];
public:
    mat() {}

    vec<DimCols, T> & operator [] (size_t const idx)
    {
        assert(idx < DimRows);
        return rows[idx];
    }

    vec<DimCols, T> const& operator [] (size_t const idx) const
    {
        assert(idx < DimRows);
        return rows[idx];
    }

    vec<DimRows, T> col(size_t const idx) const
    {
        assert(idx < DimCols);
        vec<DimRows, T> ret;
        size_t i = DimRows;

        while (i--)
        {
            ret[i] = rows[i][idx];
        }

        return ret;
    }

    void set_col(size_t idx, vec<DimRows, T> v)
    {
        assert(idx < DimCols);
        size_t i = DimRows;

        while (i--)
        {
            rows[i][idx] = v[i];
        }
    }

    static mat<DimRows, DimCols, T> identity()
    {
        mat<DimRows, DimCols,T> ret;
        size_t i = DimRows;

        while (i--)
        {
            size_t j = DimCols;
            while (j--)
            {
                ret[i][j] = (i == j);
            }
        }

        return ret;
    }

    T det() const
    {
        return dt<DimCols, T>::det(*this);
    }

    mat<DimRows - 1, DimCols - 1, T> get_minor(size_t row, size_t col) const
    {
        mat<DimRows - 1, DimCols - 1, T> ret;
        size_t i = DimRows - 1;

        while (i--)
        {
            size_t j = DimCols - 1;
            while (j--)
            {
                ret[i][j] = rows[i < row ? i : i + 1][j < col ? j : j + 1];
            }
        }

        return ret;
    }

    T cofactor(size_t row, size_t col) const
    {
        return get_minor(row, col).det() * ((row + col) % 2 ? -1 : 1);
    }

    mat<DimRows, DimCols, T> adjugate() const
    {
        mat<DimRows, DimCols, T> ret;
        size_t i = DimRows;

        while (i--)
        {
            size_t j = DimCols;
            while (j--)
            {
                ret[i][j] = cofactor(i, j);
            }
        }

        return ret;
    }

    mat<DimRows, DimCols, T> invert_transpose()
    {
        mat<DimRows, DimCols, T> ret = adjugate();
        T tmp = ret[0] * rows[0];

        return ret/tmp;
    }

    mat<DimRows, DimCols, T> invert()
    {
        return invert_transpose().transpose();
    }

    mat<DimCols, DimRows, T> transpose()
    {
        mat<DimCols, DimRows, T> ret;
        size_t i = DimCols;

        while (i--)
        {
            ret[i] = this->col(i);
        }

        return ret;
    }
};

/////////////////////////////////////////////////////////////////////////////////

template<size_t DimRows, size_t DimCols, typename T>
vec<DimRows, T> operator * (mat<DimRows, DimCols, T> const& lhs, vec<DimCols, T> const& rhs)
{
    vec<DimRows, T> ret;
    size_t i = DimRows;

    while (i--)
    {
        ret[i] = lhs[i] * rhs;
    }

    return ret;
}

template<size_t R1, size_t C1, size_t C2, typename T>
mat<R1, C2, T> operator * (mat<R1, C1, T> const& lhs, mat<C1, C2, T> const& rhs)
{
    mat<R1, C2, T> result;
    size_t i = R1;

    while (i--)
    {
        size_t j = C2;
        while (j--)
        {
            result[i][j] = lhs[i] * rhs.col(j);
        }
    }

    return result;
}

template<size_t DimRows, size_t DimCols, typename T>
mat<DimCols, DimRows, T> operator / (mat<DimRows, DimCols, T> lhs, T const& rhs)
{
    size_t i = DimRows;

    while (i--)
    {
        lhs[i] = lhs[i] / rhs;
    }

    return lhs;
}

template <size_t DimRows, size_t DimCols, class T>
std::ostream & operator << (std::ostream & out, mat<DimRows, DimCols,T> & m)
{
    for (size_t i = 0; i < DimRows; ++i)
    {
        out << m[i] << std::endl;
    }

    return out;
}

/////////////////////////////////////////////////////////////////////////////////

typedef vec<2,  float> Vec2f;
typedef vec<2,  int>   Vec2i;
typedef vec<3,  float> Vec3f;
typedef vec<3,  int>   Vec3i;
typedef vec<4,  float> Vec4f;
typedef mat<4,4,float> Matrix;

