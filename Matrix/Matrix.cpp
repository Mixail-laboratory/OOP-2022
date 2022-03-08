#include "Matrix.hpp"
#include <cmath>
#include <cstring>
#include "cassert"


Matrix::Matrix() : Cols(0), Rows(0), matrix(nullptr) {}

Matrix::Matrix(size_t cols) : Cols(cols), Rows(1), matrix(new double [cols]) {

}

Matrix::Matrix(size_t rows, size_t cols) : Cols(cols), Rows(rows), matrix(new double[cols * rows]) {
}

Matrix::Matrix(const Matrix &mat) {
    if (!mat.isValid()) {
        Cols = Rows = 0;
        matrix = nullptr;
        return;
    }
    Cols = mat.Cols;
    Rows = mat.Rows;
    matrix.reset(new double[Cols * Rows]);
    std::memcpy(matrix.get(), mat.data(), sizeof(double) * Rows * Cols);
}

bool Matrix::isValid() const {
    return !(Cols == 0 || Rows == 0 || matrix.get() == nullptr);
}

size_t Matrix::rows() const {
    return Rows;
}

size_t Matrix::cols() const {
    return Cols;
}

Matrix &Matrix::operator=(const Matrix &mat) {
    if (!mat.isValid()) {
        Cols = Rows = 0;
        matrix = nullptr;
        return *this;
    }
    if (mat.data() == matrix.get())
        return *this;
    if ((Cols != mat.Cols) || (Rows != mat.Rows))
        resize(mat.Rows, mat.Cols);
    std::memcpy(matrix.get(), mat.data(), sizeof(double) * Rows * Cols);
    return *this;
}

double *Matrix::data() {
    return matrix.get();
}

const double *Matrix::data() const {
    return matrix.get();
}

void Matrix::resize(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        Rows = Cols = 0;
    }
    if (rows != Rows || cols != Cols) {
        Rows = 0;
        Cols = 0;
        matrix = nullptr;
    } else
        return;
    Rows = rows;
    Cols = cols;
    if (this->rows() != 0 && this->cols() != 0) {
        matrix.reset(new double[Cols * Rows]);
    }
    for (size_t i = 0; i < rows*cols; i++){
        matrix.get()[i] = 0;
    }
}

const double &Matrix::coeffRef(size_t rowIdx, size_t colIdx) const {
    if (rowIdx >= Rows || colIdx >= Cols)
        throw std::out_of_range("Out of range");

    const double &ref = matrix.get()[rowIdx * Cols + colIdx];

    return ref;
}

double &Matrix::coeffRef(size_t rowIdx, size_t colIdx) {
    if (rowIdx >= Rows || colIdx >= Cols)
        throw std::out_of_range("Out of range");

    double &ref = matrix.get()[rowIdx * cols() + colIdx];

    return ref;
}

Matrix &Matrix::operator*=(const Matrix &mat) {
    if (cols() != mat.rows()) {
        Rows = Cols = 0;
        matrix.reset();
        return *this;
    }

    Matrix finalMatrix = Matrix::zeros(rows(), mat.cols());
    for (int i = 0; i < finalMatrix.rows(); i++)
        for (int j = 0; j < finalMatrix.cols(); j++)
            for (int k = 0; k < cols(); k++) {
                double temp = matrix.get()[i * cols() + k] * mat.matrix.get()[k * mat.cols() + j];
                finalMatrix.matrix.get()[i * finalMatrix.cols() + j] += temp;
            }
    *this = finalMatrix;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &mat) {
    if (rows() != mat.rows() || cols() != mat.cols()) {
        Rows = Cols = 0;
        matrix.reset();
        return *this;
    }
    for (int i = 0; i < cols() * rows(); i++)
        matrix.get()[i] += mat.matrix.get()[i];

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &mat) {
    if (rows() != mat.rows() || cols() != mat.cols()) {
        Rows = Cols = 0;
        matrix.reset();
        return *this;
    }
    for (int i = 0; i < cols() * rows(); i++)
        matrix.get()[i] -= mat.matrix.get()[i];

    return *this;
}

Matrix &Matrix::operator*=(double value) {
    if (std::isnan(value)){
        Cols = Rows = 0;
        matrix.reset();
        return *this;
    }
    for (int i = 0; i < cols() * rows(); i++)
        matrix.get()[i] *= value;
    return *this;
}

Matrix &Matrix::operator/=(double value) {
    if (value == 0)
        throw std::overflow_error("Division by zero");
    if (std::isnan(value)){
        Rows = Cols = 0;
        matrix.reset();
        return *this;
    }

    for (int i = 0; i < cols() * rows(); i++)
        matrix.get()[i] /= value;
    return *this;
}

Matrix Matrix::operator*(const Matrix &mat) const {
    if (cols() != mat.rows()) {
        return Matrix();
    }

    Matrix mult(*this);
    mult *= mat;
    return mult;
}

Matrix Matrix::operator-(const Matrix &mat) const {
    if (rows() != mat.rows() || cols() != mat.cols()) return Matrix();

    Matrix neg(*this);
    neg -= mat;
    return neg;
}

Matrix Matrix::operator+(const Matrix &mat) const {
    if (rows() != mat.rows() || cols() != mat.cols()) return Matrix();

    Matrix sum(*this);
    sum += mat;
    return sum;
}

Matrix Matrix::operator*(double value) const {
    Matrix mult(*this);
    mult *= value;
    return mult;
}

Matrix Matrix::operator/(double value) const {
    if (value == 0)
        throw std::overflow_error("Division by zero");
    if (std::isnan(value)){
        return Matrix();

    }
    Matrix division(*this);
    division /= value;
    return division;
}

Matrix &Matrix::setIdentity() {
    setZero();
    for (size_t i = 0; i < Rows * Cols; i = i + Cols + 1) {
        matrix.get()[i] = 1.0;
    }
    return *this;
}

Matrix &Matrix::setZero() {
    return setConstants(0);
}

Matrix &Matrix::setConstants(double value) {
    if (std::isnan(value)){
        Rows = Cols = 0;
        matrix.reset();
        return *this;
    }
    for(size_t i = 0; i < rows() * cols(); i ++)
        matrix.get()[i] = value;
    return *this;
 }

Matrix &Matrix::setIdentity(size_t rows, size_t cols) {
    resize(rows, cols);
    setIdentity();
    return *this;
}

Matrix &Matrix::setZero(size_t rows, size_t cols) {
    resize(rows, cols);
    setZero();
    return *this;
}

Matrix &Matrix::setConstants(size_t rows, size_t cols, double value) {
    resize(rows, cols);
    setConstants(value);
    return *this;
}

Matrix Matrix::identity(size_t rows, size_t cols) {
    Matrix ident = Matrix(rows, cols);
    ident.setIdentity();
    return ident;
}

Matrix Matrix::zeros(size_t rows, size_t cols) {
    Matrix ident = Matrix(rows, cols);
    ident.setZero();
    return ident;
}

Matrix Matrix::constants(size_t rows, size_t cols, double value) {
    Matrix ident = Matrix(rows, cols);
    ident.setConstants(value);
    return ident;
}

Matrix operator*(double value, const Matrix &mat) {
    return mat * value;
}

double Matrix::det() const {
    if (Cols != Rows || !isValid())
        return NAN;

    Matrix _temp(*this);
    double det = 1;

    for (size_t j = 0; j < _temp.cols(); j++) {
        if (_temp.coeffRef(j, j) == 0) {
            size_t i = j + 1;
            for (; i < _temp.rows() && _temp.coeffRef(i, j) == 0; i++);
            if (i == _temp.rows())
                return 0;
            _temp.change_lines(i, j, -1);
        }

        det *= _temp.coeffRef(j, j);
        for (size_t i = j + 1; i < _temp.Rows; i++) {
            if (_temp.coeffRef(i, j) != 0) {
                double temp = -_temp.coeffRef(i, j) / _temp.coeffRef(j, j);
                for (size_t k = 0; k < _temp.Cols; k++) {
                    _temp.coeffRef(i, k) += _temp.coeffRef(j, k) * temp;
                }
            }

        }
    }
    return det;
}

Matrix &Matrix::change_lines(size_t line1, size_t line2, int sign) {
    assert(sign == 1 || sign == -1);
    if (line1 >= rows() || line2 >= rows()) throw std::out_of_range("out of range");
    for (size_t k = 0; k < cols(); k++) {
        double temp = coeffRef(line1, k) * sign;
        coeffRef(line1, k) = coeffRef(line2, k);
        coeffRef(line2, k) = temp;
    }
    return *this;
}

Matrix Matrix::transpose() const {
    if (cols() != rows() || !isValid())
        return Matrix();

    Matrix _matrix(cols(), rows());
    for (size_t i = 0; i < Rows; i++) {
        for (size_t j = 0; j < Cols; j++)
            _matrix.coeffRef(j, i) = coeffRef(i, j);
    }

    return _matrix;
}

Matrix Matrix::diag() const {
    if (cols() != rows() || !isValid()) return Matrix();

    Matrix _temp(*this);

    for (size_t j = 0; j < _temp.rows(); j++) {

        if (_temp.coeffRef(j, j) == 0) {
            size_t i = j + 1;
            for (; i < rows() && coeffRef(i, j) == 0; ++i);
            if (i == rows()) return Matrix();
            _temp.change_lines(i, j, -1);
        }

        for (size_t k = j + 1; k < _temp.rows(); k++) {
            double temp = -_temp.coeffRef(k, j) / _temp.coeffRef(j, j);
            for (size_t l = 0; l < _temp.cols(); l++)
                _temp.coeffRef(k, l) += _temp.coeffRef(j, l) * temp;

        }
    }

    for (long int j = _temp.rows() - 1; j >= 0; j--) {
        if (_temp.coeffRef(j, j) == 0) {
            long int i = j - 1;
            for (; i < rows() && coeffRef(i, j) == 0; i--);
            _temp.change_lines(i, j, -1);
        }

        for (long int k = j - 1; k >= 0; k--) {
            double temp = -_temp.coeffRef(k, j) / _temp.coeffRef(j, j);
            for (long int l = 0; l < _temp.cols(); l++)
                _temp.coeffRef(k, l) += _temp.coeffRef(j, l) * temp;
        }
    }

    return _temp;
}

Matrix Matrix::inverse() const {
    if (cols() != rows() || !isValid() || det() == 0) return Matrix();

    Matrix _temp(*this);
    Matrix ident = Matrix::identity(rows(), cols());

    for (size_t j = 0; j < _temp.rows(); j++) {

        if (_temp.coeffRef(j, j) == 0) {
            size_t i = j + 1;
            for (; i < rows() && coeffRef(i, j) == 0; ++i);
            if (i == rows()) return Matrix();
            _temp.change_lines(i, j);
            ident.change_lines(i, j);
        }

        double temp_ident = _temp.coeffRef(j, j);
        for (size_t i = 0; i < _temp.cols(); i++) {
            _temp.coeffRef(j, i) /= temp_ident;
            ident.coeffRef(j, i) /= temp_ident;
        }


        for (size_t k = j + 1; k < _temp.rows(); k++) {
            double temp = _temp.coeffRef(k, j) / _temp.coeffRef(j, j);
            for (size_t l = 0; l < _temp.cols(); l++) {
                _temp.coeffRef(k, l) -= _temp.coeffRef(j, l) * temp;
                ident.coeffRef(k, l) -= ident.coeffRef(j, l) * temp;
            }

        }
    }

    for (long int j = _temp.rows() - 1; j >= 0; j--) {
        if (_temp.coeffRef(j, j) == 0) {
            long int i = j - 1;
            for (; i < rows() && coeffRef(i, j) == 0; i--);
            _temp.change_lines(i, j);
            ident.change_lines(i, j);
        }

        for (long int k = j - 1; k >= 0; k--) {
            double temp = _temp.coeffRef(k, j) / _temp.coeffRef(j, j);
            for (long int l = 0; l < _temp.cols(); l++) {
                _temp.coeffRef(k, l) -= _temp.coeffRef(j, l) * temp;
                ident.coeffRef(k, l) -= ident.coeffRef(j, l) * temp;
            }
        }
    }
    return ident;
}


Matrix::~Matrix() = default;




