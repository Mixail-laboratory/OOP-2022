#pragma once
#include <cstdlib>
#include <memory>

class Matrix final {
public:
    Matrix();

    explicit Matrix(size_t cols);

    Matrix(size_t rows, size_t cols);

    ~Matrix();

    Matrix(const Matrix &mat);

    Matrix operator*(const Matrix &mat) const;

    Matrix operator-(const Matrix &mat) const;

    Matrix operator+(const Matrix &mat) const;

    Matrix operator*(double value) const;

    Matrix operator/(double value) const;

    Matrix &operator=(const Matrix &mat);

    Matrix &operator*=(const Matrix &mat);

    Matrix &operator+=(const Matrix &mat);

    Matrix &operator-=(const Matrix &mat);

    Matrix &operator*=(double value);

    Matrix &operator/=(double value);

    [[nodiscard]] bool isValid() const;

    void resize(size_t rows, size_t cols);

    [[nodiscard]] const double &coeffRef(size_t rowIdx, size_t colIdx) const;

    double &coeffRef(size_t rowIdx, size_t colIdx);

    const double *data() const;

    double *data();

    [[nodiscard]] size_t rows() const;

    [[nodiscard]] size_t cols() const;

    Matrix &setIdentity();

    Matrix &setZero();

    Matrix &setConstants(double value);

    Matrix &setIdentity(size_t rows, size_t cols);

    Matrix &setZero(size_t rows, size_t cols);

    Matrix &setConstants(size_t rows, size_t cols, double value);

    [[nodiscard]] Matrix diag() const;

    [[nodiscard]] Matrix transpose() const;

    [[nodiscard]] Matrix inverse() const;

    [[nodiscard]] double det() const;

    [[nodiscard]] static Matrix identity(size_t rows, size_t cols) ;

    [[nodiscard]] static Matrix zeros(size_t rows, size_t cols) ;

    [[nodiscard]] static Matrix constants(size_t rows, size_t cols, double value) ;

    friend Matrix operator*(double value, const Matrix &mat);

private:
    size_t Cols; //столбец
    size_t Rows; //строка
    std::unique_ptr<double> matrix;
    Matrix& change_lines(size_t line1, size_t line2, int sign = 1);

};
