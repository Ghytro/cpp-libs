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

template<class T>
class Matrix
{
    public:
        Matrix();
        Matrix(size_t lines, size_t cols);
        Matrix(size_t lines, size_t cols, T** matr);
        Matrix(const Matrix<T>& matr);
        virtual ~Matrix();

        Matrix& operator =(const Matrix& right);

        T* operator [](const int index);

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

        size_t lines();
        size_t cols();
        T det();

    protected:
        T **matr;
        size_t _lines;
        size_t _cols;

    private:
        static T _det(Matrix<T> m);
};

/**< ****************************************************/
/**< C-tors & D-tors */

template<class T>
Matrix<T>::Matrix(): matr(nullptr), _lines(0), _cols(0) {}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& matr)
{
    *this = matr;
}

template<class T>
Matrix<T>::Matrix(size_t lines, size_t cols)
{
    //ctor
    this->matr = new T*[lines];
    for (size_t i = 0; i < lines; ++i)
        this->matr[i] = new T[cols];
    for (size_t i = 0; i < lines; ++i)
        for (size_t j = 0; j < cols; ++j)
            this->matr[i][j] = T(0);
    this->_lines = lines;
    this->_cols = cols;
}

template<class T>
Matrix<T>::Matrix(size_t lines, size_t cols, T** matr)
{
    //here you can assign a matrix from matr
    Matrix::Matrix(lines, cols);
    for (size_t i = 0; i < this->lines(); ++i)
        for (size_t j = 0; j < this->cols(); ++j)
            this->matr[i][j] = matr[i][j];
}

template<class T>
Matrix<T>::~Matrix()
{
    //dtor
    delete matr;
}

/**< Getters for special info about matrix */

template<class T>
size_t Matrix<T>::lines()
{
    return this->_lines;
}

template<class T>
size_t Matrix<T>::cols()
{
    return this->_cols;
}

/**< Operators */

template<class T>
T* Matrix<T>::operator [](const int index)
{
    return this->matr[index];
}

template<class T>
Matrix<T>& Matrix<T>::operator =(const Matrix& right)
{
    if (this == &right)
        return *this;
    this->matr = right.matr;
    this->_lines = right._lines;
    this->_cols = right._cols;
    return *this;
}

template<class T>
Matrix<T> operator +(const Matrix<T>& left, const Matrix<T>& right)
{
    //insert exception if sizes differ here
    Matrix<T> r(left._lines, left._cols);
    for (int i = 0; i < left._lines; ++i)
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
    Matrix<T> r(right._lines, right._cols);
    for (size_t i = 0; i < right._lines; ++i)
    {
        for (size_t j = 0; j < right._cols; ++j)
        {
            r[i][j] = right.matr[i][j] * left;
        }
    }
    return r;
}

template<class T>
Matrix<T> operator *(const Matrix<T> &left, const int& right)
{
    Matrix<T> r(left._lines, left._cols);
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
    Matrix<T> r(left._lines, right._cols);
    for (size_t i = 0; i < left._lines; ++i)
    {
        for (size_t j = 0; j < right._cols; ++j)
        {
            for (size_t k = 0; k < left._cols; ++k)
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
        Matrix<T> temp(m.lines() - 1, m.cols() - 1);
        for (size_t j = 1; j < m.lines(); ++j)
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
