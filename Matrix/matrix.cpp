#include "matrix.h"

/**< ****************************************************/
/**< C-tors & D-tors */

Matrix::Matrix(const Matrix& matr)
{
    *this = matr;
}

Matrix::Matrix(size_t rows, size_t cols)
{
    //ctor
    this->matr = std::vector<std::vector<double>>(rows, std::vector<double>(cols));
}

Matrix::Matrix(double** matr, size_t rows, size_t cols)
{
    //here you can assign a matrix from matr
    this->matr = std::vector<std::vector<double>>(rows, std::vector<double>(cols));
    for (size_t i = 0; i < this->rows(); ++i)
        for (size_t j = 0; j < this->cols(); ++j)
            this->matr[i][j] = matr[i][j];
}

Matrix::Matrix(const std::vector<std::vector<double>>& matr)
{
    this->matr = matr;
}

Matrix::~Matrix(){}
/**< Getters for special info about matrix */

size_t Matrix::rows() const
{
    return this->matr.size();
}

size_t Matrix::cols() const
{
    return this->matr.front().size();
}

/**< Operators */

std::vector<double>& Matrix::operator [](const int index)
{
    return this->matr[index];
}

std::vector<double> Matrix::operator [](const int index) const
{
    return this->matr[index];
}

Matrix& Matrix::operator =(const Matrix& right)
{
    if (this == &right)
        return *this;
    this->matr = right.matr;
    return *this;
}

Matrix& Matrix::operator =(const std::vector<std::vector<double>> &right)
{
    this->matr = right;
    return *this;
}
Matrix operator +(const Matrix& left, const Matrix& right)
{
    if (left.rows() != right.rows() || left.cols() != right.cols())
        throw IncorrectMatrixAdditionException();
    Matrix r(left.rows(), left.cols());
    for (size_t i = 0; i < left.rows(); ++i)
        for (size_t j = 0; j < left.cols(); ++j)
            r[i][j] = left.matr[i][j] + right.matr[i][j];
    return r;
}

Matrix& Matrix::operator +=(const Matrix& right)
{
    *this = *this + right;
    return *this;
}

Matrix operator -(const Matrix& left, const Matrix& right)
{
    return left + (-1*right);
}

Matrix& Matrix::operator-=(const Matrix& right)
{
    *this = *this - right;
    return *this;
}

Matrix operator *(const double& left, const Matrix &right)
{
    Matrix r(right.rows(), right.cols());
    for (size_t i = 0; i < right.rows(); ++i)
        for (size_t j = 0; j < right.cols(); ++j)
            r[i][j] = right.matr[i][j] * left;
    return r;
}

Matrix operator *(const Matrix &left, const int& right)
{
    Matrix r(left.rows(), left.cols());
    r = right * left;
    return r;
}

Matrix& Matrix::operator *=(const int& right)
{
    *this = *this * right;
    return *this;
}

Matrix operator *(const Matrix& left, const Matrix &right)
{
    if (left.cols() != right.rows())
        throw IncorrectMatrixMultiplicationException();

    Matrix r(left.rows(), right.cols());
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

Matrix& Matrix::operator *= (const Matrix& right)
{
    *this = *this * right;
    return *this;
}

//advance this operator with printing width (printf)
std::ostream& operator <<(std::ostream& os, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.rows(); ++i)
    {
        for (size_t j = 0; j < matrix.cols(); ++j)
            os << matrix[i][j] << " ";
        os << "\n";
    }
    return os;
}

/**< Operations */
double Matrix::det()
{
    if (this->rows() != this->cols())
        throw NotSquareMatrixException();

    return _det(*this);
}

double Matrix::_det(Matrix m)
{
    if (m.cols() == 1)
        return m[0][0];

    if (m.cols() == 2)
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];

    double r(0);
    for (size_t i = 0; i < m.cols(); ++i)
    {
        Matrix temp(m.rows() - 1, m.cols() - 1);
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
        r += (((i + 1) % 2) ? double(1) : double(-1)) * m[0][i] * _det(temp);
    }
    return r;
}

Matrix Matrix::transpose()
{
    std::vector<std::vector<double>> ans(this->cols(), std::vector<double>(this->rows()));
    for (size_t i = 0; i < this->rows(); ++i)
        for (size_t j = 0; j < this->cols(); ++j)
            ans[i][j] = matr[j][i];
    return Matrix(ans);
}

double Matrix::minor(size_t row, size_t col)
{
    if (this->rows() != this->cols())
        throw NotSquareMatrixException();

    Matrix temp(this->rows() - 1, this->cols() - 1);
    bool passed_row = false;
    for (size_t i = 0; i < temp.rows(); ++i)
    {
        passed_row |= (i == row);
        bool passed_col = false;
        for (size_t j = 0; j < temp.cols(); ++j)
        {
            passed_col |= (j == col);
            temp[i][j] = this->matr[i + passed_row][j + passed_col];
        }
    }
    return temp.det();
}

Matrix Matrix::minor_matrix()
{
    Matrix ans(this->rows(), this->cols());
    for (size_t i = 0; i < this->rows(); ++i)
        for (size_t j = 0; j < this->cols(); ++j)
            ans[i][j] = this->minor(i, j);
    return ans;
}

double Matrix::cofactor(size_t row, size_t col)
{
    return (((row + col + 2) % 2 == 0) ? (this->minor(row, col)) : (-this->minor(row, col)));
}

Matrix Matrix::cofactor_matrix()
{
    Matrix ans(this->rows(), this->cols());
    for (size_t i = 0; i < this->rows(); ++i)
        for (size_t j = 0; j < this->cols(); ++j)
            ans[i][j] = this->cofactor(i, j);
    return ans;
}

Matrix Matrix::inverse()
{
    double det = this->det();
    if (det == 0)
        throw NullDeterminantException();
    return (1.0 / det) * this->cofactor_matrix().transpose();
}

Matrix Matrix::E(size_t size)
{
    Matrix ans(size, size);
    for (size_t i = 0; i < size; ++i)
        ans[i][i] = 1;
    return ans;
}

/* EXCEPTION CLASSES MESSAGES ***************/
const char* NotSquareMatrixException::what() const throw()
{
    return "The operation cannot be applied to not-square matrix.";
}

const char* NullDeterminantException::what() const throw()
{
    return "The operation cannot be applied to matrix because it's determinant equals zero.";
}

const char* IncorrectMatrixMultiplicationException::what() const throw()
{
    return "Matrices sizes doesn't match: impossible to multiply.";
}

const char* IncorrectMatrixAdditionException::what() const throw()
{
    return "Matrices sizes doesn't match: impossible to add.";
}
