#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>
#include <exception>
class Matrix
{
    public:
        Matrix(size_t rows, size_t cols);
        Matrix(double** matr, size_t rows, size_t cols);
        Matrix(const std::vector<std::vector<double>>& matr);
        Matrix(const Matrix& matr);
        ~Matrix();

        Matrix& operator =(const Matrix& right);
        Matrix& operator =(const std::vector<std::vector<double>> &right);

        std::vector<double>& operator [](const int index);
        std::vector<double> operator [](const int index) const;

        friend Matrix operator +(const Matrix& left, const Matrix& right);

        Matrix& operator +=(const Matrix& right);

        friend Matrix operator -(const Matrix& left, const Matrix& right);

        Matrix& operator -=(const Matrix& right);

        friend Matrix operator *(const double& left, const Matrix &right);

        Matrix& operator *=(const int& right);

        friend Matrix operator *(const Matrix &left, const int& right);

        friend Matrix operator *(const Matrix& left, const Matrix& right);

        Matrix& operator *= (const Matrix& right);

        size_t rows() const;
        size_t cols() const;
        double det();
        Matrix transpose();
        double minor(size_t row, size_t col);
        Matrix minor_matrix();
        double cofactor(size_t row, size_t col);
        Matrix cofactor_matrix();
        Matrix inverse();

        static Matrix E(size_t size);

    protected:
        std::vector<std::vector<double>> matr;

    private:
        static double _det(Matrix m);
};
std::ostream& operator <<(std::ostream& os, const Matrix& matrix);

class NotSquareMatrixException: public std::exception
{
public:
    const char* what() const throw();
};

class NullDeterminantException: public std::exception
{
public:
    const char* what() const throw();
};

class IncorrectMatrixMultiplicationException: public std::exception
{
public:
    const char* what() const throw();
};

class IncorrectMatrixAdditionException: public std::exception
{
public:
    const char* what() const throw();
};

#endif // MATRIX_H
