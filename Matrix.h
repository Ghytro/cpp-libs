#ifndef MATRIX_H
#define MATRIX_H

#if !defined(_SIZE_T) && !defined(_SIZE_T_DEFINED)
#  define _SIZE_T_DEFINED
#if defined(_WIN64)
   typedef unsigned __int64 size_t;
#else
   typedef unsigned int size_t;
#endif
#  if defined(__cplusplus)
#    define _SIZE_T std::size_t
#  else
#    define _SIZE_T size_t
#  endif
#endif

#include <vector>
template<class T>
class Matrix
{
    public:
        Matrix(size_t rows, size_t cols);
        Matrix(T** matr, size_t rows, size_t cols);
        Matrix(const std::vector<std::vector<T>>& matr);
        Matrix(const Matrix<T>& matr);
        ~Matrix();

        Matrix& operator =(const Matrix& right);
        Matrix& operator =(const std::vector<std::vector<T>> &right);

        std::vector<T>& operator [](const int index);

        template<class TT>
        friend Matrix<TT> operator +(const Matrix<TT>& left, const Matrix<TT>& right);

        Matrix& operator +=(const Matrix& right);

        template<class TT>
        friend Matrix<TT> operator -(const Matrix<TT>& left, const Matrix<TT>& right);

        Matrix& operator -=(const Matrix& right);

        template<class TT>
        friend Matrix<TT> operator *(const int& left, const Matrix<TT> &right);

        Matrix& operator *=(const int& right);

        template<class TT>
        friend Matrix<TT> operator *(const Matrix<TT> &left, const int& right);

        template<class TT>
        friend Matrix<TT> operator *(const Matrix<TT>& left, const Matrix<TT>& right);

        Matrix& operator *= (const Matrix& right);

        size_t rows();
        size_t cols();
        T det();

    protected:
        std::vector<std::vector<T>> matr;

    private:
        static T _det(Matrix<T> m);
};

/**< ****************************************************/
/**< C-tors & D-tors */

template<class T>
Matrix<T>::Matrix(const Matrix<T>& matr)
{
    *this = matr;
}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
    //ctor
    this->matr = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
}

template<class T>
Matrix<T>::Matrix(T** matr, size_t rows, size_t cols)
{
    //here you can assign a matrix from matr
    this->matr = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
    for (size_t i = 0; i < this->rows(); ++i)
        for (size_t j = 0; j < this->cols(); ++j)
            this->matr[i][j] = matr[i][j];
}

template<class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& matr)
{
    this->matr = matr;
}

template<class T>
Matrix<T>::~Matrix(){}
/**< Getters for special info about matrix */

template<class T>
size_t Matrix<T>::rows()
{
    return this->matr.size();
}

template<class T>
size_t Matrix<T>::cols()
{
    return this->matr.front().size();
}

/**< Operators */

template<class T>
std::vector<T>& Matrix<T>::operator [](const int index)
{
    return this->matr[index];
}

template<class T>
Matrix<T>& Matrix<T>::operator =(const Matrix& right)
{
    if (this == &right)
        return *this;
    this->matr = right.matr;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator =(const std::vector<std::vector<T>> &right)
{
    this->matr = right;
    return *this;
}

template<class T>
Matrix<T> operator +(const Matrix<T>& left, const Matrix<T>& right)
{
    //insert exception if sizes differ here
    Matrix<T> r(left._rows, left._cols);
    for (int i = 0; i < left._rows; ++i)
        for (int j = 0; j < left._cols; ++j)
            r[i][j] = left.matr[i][j] + right.matr[i][j];
    return r;
}

template<class T>
Matrix<T>& Matrix<T>::operator +=(const Matrix<T>& right)
{
    *this = *this + right;
    return *this;
}

template<class T>
Matrix<T> operator -(const Matrix<T>& left, const Matrix<T>& right)
{
    return left + (-1*right);
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& right)
{
    *this = *this - right;
    return *this;
}

template<class T>
Matrix<T> operator *(const int& left, const Matrix<T> &right)
{
    Matrix<T> r(right.rows(), right.cols());
    for (size_t i = 0; i < right.rows(); ++i)
    {
        for (size_t j = 0; j < right.cols(); ++j)
        {
            r[i][j] = right.matr[i][j] * left;
        }
    }
    return r;
}

template<class T>
Matrix<T> operator *(const Matrix<T> &left, const int& right)
{
    Matrix<T> r(left.rows(), left.cols());
    r = right * left;
    return r;
}

template<class T>
Matrix<T>& Matrix<T>::operator *=(const int& right)
{
    *this = *this * right;
    return *this;
}

template<class T>
Matrix<T> operator *(const Matrix<T>& left, const Matrix<T> &right)
{
    //insert exception if impossible to multiply
    Matrix<T> r(left.rows(), right.cols());
    for (size_t i = 0; i < left.rows(); ++i)
    {
        for (size_t j = 0; j < right.cols(); ++j)
        {
            for (size_t k = 0; k < left.cols(); ++k)
            {
                r[i][j] += left.matr[i][k] * right.matr[k][j];
            }
        }
    }
    return r;
}

template <class T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& right)
{
    *this = *this * right;
    return *this;
}

/**< Operations */
template<class T>
T Matrix<T>::det()
{
    //exception if matrix is not square here
    return _det(*this);
}

template<class T>
T Matrix<T>::_det(Matrix<T> m)
{
    if (m.cols() == 2)
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];

    T r = 0;
    for (size_t i = 0; i < m.cols(); ++i)
    {
        Matrix<T> temp(m.rows() - 1, m.cols() - 1);
        for (size_t j = 1; j < m.rows(); ++j)
        {
            bool x = 0;
            for (size_t k = 0; k < m.cols(); ++k)
            {
                if (k == i)
                {
                    x = 1;
                    continue;
                }
                temp[j - 1][k - x] = m[j][k];
            }
        }
        r += (((i + 1) % 2) ? (1) : (-1)) * m[0][i] * _det(temp);
    }
    return r;
}
#endif // MATRIX_H
