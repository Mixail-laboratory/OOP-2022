#include "gtest/gtest.h"
#include <cmath>
#include "../../Matrix.hpp"


TEST(constructor, null_constr) {
    Matrix m(0);
    EXPECT_EQ(m.isValid(), false);
    Matrix n(0, 0);
    EXPECT_EQ(n.isValid(), false);
}

TEST(constructor, null_copy) {
    Matrix m(0);
    Matrix n(m);
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0);
    Matrix p(l);
    EXPECT_EQ(p.isValid(), false);
}

TEST(constructor, null_cols_or_rows) {
    Matrix n(0, 1), m(1, 0);
    EXPECT_EQ(m.isValid(), false);
    EXPECT_EQ(n.isValid(), false);
    Matrix l(n), p(m);
    EXPECT_EQ(l.isValid(), false);
    EXPECT_EQ(p.isValid(), false);

}

TEST(constructor, normal_matrix) {
    Matrix m(1, 1);
    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.cols(), 1);
    Matrix p(m);
    EXPECT_EQ(p.rows(), 1);
    EXPECT_EQ(p.cols(), 1);
}

TEST(coeffRef, null_matrix) {
    Matrix l(0, 0);
    EXPECT_ANY_THROW(l.coeffRef(0, 0));
    Matrix m(0);
    EXPECT_ANY_THROW(m.coeffRef(0, 0));
}


TEST(matrix_composition, null_matrix) {
    Matrix m(0), n(0), p;
    p = m * n;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), a(0, 0), c(0, 0);
    c = l * a;
    EXPECT_EQ(c.isValid(), false);
}

TEST(difference, null_matrix) {
    Matrix m(0), n(0), p;
    p = m - n;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), a(0, 0), c(0, 0);
    c = l - a;
    EXPECT_EQ(c.isValid(), false);
}

TEST(sum, null_matrix) {
    Matrix m(0), n(0), p;
    p = m + n;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), a(0, 0), c(0, 0);
    c = l + a;
    EXPECT_EQ(c.isValid(), false);
}

TEST(value_composition, null_matrix) {
    Matrix m(0), p;
    p = m * 2.0;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c = l * 2.0;
    EXPECT_EQ(c.isValid(), false);
}

TEST(value_composition, null_matrix_NAN_value) {
    Matrix m(0), p;
    p = m * NAN;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c = l * NAN;
    EXPECT_EQ(c.isValid(), false);
}

TEST(value_division, null_matrix) {
    Matrix m(0), p;
    p = m / 2.0;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c = l / 2.0;
    EXPECT_EQ(c.isValid(), false);
}

TEST(value_division, null_matrix_NAN_value) {
    Matrix m(0), p;
    p = m / NAN;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c = l / NAN;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality, null_matrix) {
    Matrix m(0), p;
    p = m;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c = l;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality_matrix_composition, null_matrix) {
    Matrix m(0), p;
    p *= m;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c *= l;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality_difference, null_matrix) {
    Matrix m(0), p;
    p -= m;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c -= l;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality_sum, null_matrix) {
    Matrix m(0), p;
    p += m;
    EXPECT_EQ(p.isValid(), false);
    Matrix l(0, 0), c(0, 0);
    c += l;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality_value_composition, null_matrix) {
    Matrix p;
    p *= 2.0;
    EXPECT_EQ(p.isValid(), false);
    Matrix c(0, 0);
    c *= 2.0;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality_value_composition, null_matrix_NAN_value) {
    Matrix p;
    p *= NAN;
    EXPECT_EQ(p.isValid(), false);
    Matrix c(0, 0);
    c *= NAN;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality_value_division, null_matrix) {
    Matrix p;
    p /= 2.0;
    EXPECT_EQ(p.isValid(), false);
    Matrix c(0, 0);
    c *= 2.0;
    EXPECT_EQ(c.isValid(), false);
}

TEST(equality_value_division, null_matrix_NAN_value) {
    Matrix p;
    p /= NAN;
    EXPECT_EQ(p.isValid(), false);
    Matrix c(0, 0);
    c /= NAN;
    EXPECT_EQ(c.isValid(), false);
}

TEST(isValid, null_matrix) {

    Matrix m(0);
    EXPECT_EQ(m.isValid(), false);
    Matrix n(0, 0);
    EXPECT_EQ(n.isValid(), false);
}

TEST(resize, null_cols_rows) {
    Matrix m(0, 0);
    m.resize(0, 0);
    EXPECT_EQ(m.isValid(), false);
}

TEST(resize, null_cols_or_rows) {
    Matrix m(0, 0);
    m.resize(0, 1);
    EXPECT_EQ(m.isValid(), false);
    m.resize(1, 0);
    EXPECT_EQ(m.isValid(), false);
}

TEST(setIdentity, null_matrix) {
    Matrix m(0, 0);
    m.setIdentity();
    EXPECT_EQ(m.isValid(), false);
    m.setIdentity(0, 0);
    EXPECT_EQ(m.isValid(), false);
}

TEST(setzero, null_matrix) {
    Matrix m(0, 0);
    m.setZero();
    EXPECT_EQ(m.isValid(), false);
    m.setZero(0, 0);
    EXPECT_EQ(m.isValid(), false);
}

TEST(setConstants, null_matrix_NAN_constant) {
    Matrix m(0);
    m.setConstants(NAN);
    EXPECT_EQ(m.isValid(), false);
    m.setConstants(0, 0, NAN);
    EXPECT_EQ(m.isValid(), false);
}

TEST(setConstants, null_matrix) {
    Matrix m(0);
    m.setConstants(2.0);
    EXPECT_EQ(m.isValid(), false);
    m.setConstants(0, 0, 2.0);
    EXPECT_EQ(m.isValid(), false);
}

TEST(det, null_matrix) {
    Matrix m(0);
    EXPECT_EQ(std::isnan(m.det()), true);
    Matrix n(0, 0);
    EXPECT_EQ(std::isnan(n.det()), true);
}

TEST(diag, null_matrix) {
    Matrix m(0);
    m.diag();
    EXPECT_EQ(m.isValid(), false);
    Matrix n(0, 0);
    n.diag();
    EXPECT_EQ(n.isValid(), false);
}

TEST(transpose, null_matrix) {
    Matrix m(0);
    m.transpose();
    EXPECT_EQ(m.isValid(), false);
    Matrix n(0, 0);
    n.transpose();
    EXPECT_EQ(n.isValid(), false);
}

TEST(inverse, null_matrix) {
    Matrix m(0);
    m.inverse();
    EXPECT_EQ(m.isValid(), false);
    Matrix n(0, 0);
    n.inverse();
    EXPECT_EQ(n.isValid(), false);
}

TEST(friend_value_composition, null_matrix) {
    Matrix m(0), n;
    n = 2.0 * m;
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0), p;
    p = 2.0 * l;
    EXPECT_EQ(p.isValid(), false);
}

TEST(friend_value_composition, null_matrix_NAN_value) {
    Matrix m(0), n;
    n = NAN * m;
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0), p;
    p = NAN * l;
    EXPECT_EQ(p.isValid(), false);
}

TEST(identity, null_cols_rows) {
    Matrix m(0), n;
    n.identity(0, 0);
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0), p;
    p.identity(0, 0);
    EXPECT_EQ(p.isValid(), false);
}

TEST(zero, null_cols_rows) {
    Matrix m(0), n;
    n.zeros(0, 0);
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0), p;
    p.zeros(0, 0);
    EXPECT_EQ(p.isValid(), false);
}

TEST(constant, null_cols_rows_NAN_value) {
    Matrix m(0), n;
    n.constants(0, 0, NAN);
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0), p;
    p.constants(0, 0, NAN);
    EXPECT_EQ(p.isValid(), false);
}

TEST(constant, null_cols_rows) {
    Matrix m(0), n;
    n.constants(0, 0, 2.0);
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0), p;
    p.constants(0, 0, 2.0);
    EXPECT_EQ(p.isValid(), false);
}

TEST(identity, null_cols_or_rows) {
    Matrix m(0, 0), n;
    n.identity(0, 1);
    EXPECT_EQ(n.rows(), 0);
    EXPECT_EQ(n.cols(), 0);
    Matrix l(0, 0), p;
    p.identity(1, 0);
    EXPECT_EQ(p.rows(), 0);
    EXPECT_EQ(p.cols(), 0);
}

TEST(zero, null_cols_or_rows) {
    Matrix m(0, 0), n;
    n.zeros(0, 1);
    EXPECT_EQ(n.rows(), 0);
    EXPECT_EQ(n.cols(), 0);
    Matrix l(0, 0), p;
    p.zeros(1, 0);
    EXPECT_EQ(p.rows(), 0);
    EXPECT_EQ(p.cols(), 0);
}

TEST(constant, null_cols_or_rows_NAN_value) {
    Matrix m(0, 0), n;
    n.constants(0, 1, NAN);
    EXPECT_EQ(n.rows(), 0);
    EXPECT_EQ(n.cols(), 0);
    Matrix l(0, 0), p;
    p.constants(1, 0, NAN);
    EXPECT_EQ(p.rows(), 0);
    EXPECT_EQ(p.cols(), 0);
}

TEST(constant, null_cols_or_rows) {
    Matrix m(0), n;
    n.constants(0, 1, 2.0);
    EXPECT_EQ(n.isValid(), false);
    Matrix l(0, 0), p;
    p.constants(1, 0, 2.0);
    EXPECT_EQ(p.isValid(), false);
}

TEST(constructor, new_matrix) {
    Matrix m(5);
    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.cols(), 5);
    Matrix n(2, 5);
    EXPECT_EQ(n.rows(), 2);
    EXPECT_EQ(n.cols(), 5);
}

TEST(setzero, new_matrix) {
    Matrix m(5);
    m.setZero();
    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.cols(), 5);
    EXPECT_EQ(m.coeffRef(0, 2), 0);
    EXPECT_ANY_THROW(m.coeffRef(0, 5));
    m.setZero(4, 6);
    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 6);
    EXPECT_EQ(m.coeffRef(2, 3), 0);
    EXPECT_ANY_THROW(m.coeffRef(25, 4));
    Matrix n(5, 6);
    n.setZero();
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.cols(), 6);
    EXPECT_EQ(n.coeffRef(4, 5), 0);
    EXPECT_ANY_THROW(n.coeffRef(6, 7));
}

TEST(setIdentity, new_matrix) {
    Matrix m(5);
    m.setIdentity();
    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.cols(), 5);
    EXPECT_DOUBLE_EQ(m.coeffRef(0, 2), 0);
    EXPECT_ANY_THROW(m.coeffRef(0, 6));
    m.setIdentity(4, 6);
    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 6);
    EXPECT_EQ(m.coeffRef(2, 3), 0);
    EXPECT_EQ(m.coeffRef(2, 2), 1);
    EXPECT_ANY_THROW(m.coeffRef(25, 4));
    Matrix n(5, 6);
    n.setIdentity();
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.cols(), 6);
    EXPECT_EQ(n.coeffRef(4, 5), 0);
    EXPECT_EQ(n.coeffRef(4, 4), 1);
    EXPECT_ANY_THROW(n.coeffRef(6, 7));
}

TEST(setConstants, new_matrix) {
    Matrix m(5);
    m.setConstants(5.0);
    EXPECT_EQ(m.rows(), 1);
    EXPECT_EQ(m.cols(), 5);
    EXPECT_EQ(m.coeffRef(0, 2), 5.0);
    EXPECT_ANY_THROW(m.coeffRef(0, 5));
    m.setConstants(4, 6, 5.0);
    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 6);
    EXPECT_EQ(m.coeffRef(2, 3), 5.0);
    EXPECT_ANY_THROW(m.coeffRef(25, 4));
    Matrix n(5, 6);
    n.setConstants(5.0);
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.cols(), 6);
    EXPECT_EQ(n.coeffRef(4, 5), 5.0);
    EXPECT_ANY_THROW(n.coeffRef(6, 7));
}

TEST(setConstants, new_matrix_NAN_value) {
    Matrix m(5);
    m.setConstants(NAN);
    EXPECT_EQ(m.rows(), 0);
    EXPECT_EQ(m.cols(), 0);
    EXPECT_ANY_THROW(m.coeffRef(2, 0));
    EXPECT_ANY_THROW(m.coeffRef(0, 5));
    m.setConstants(4, 6, NAN);
    EXPECT_EQ(m.rows(), 0);
    EXPECT_EQ(m.cols(), 0);
    EXPECT_ANY_THROW(m.coeffRef(2, 3));
    EXPECT_ANY_THROW(m.coeffRef(25, 4));
    Matrix n(5, 6);
    n.setConstants(NAN);
    EXPECT_EQ(n.rows(), 0);
    EXPECT_EQ(n.cols(), 0);
    EXPECT_ANY_THROW(n.coeffRef(4, 5));
    EXPECT_ANY_THROW(n.coeffRef(6, 7));
}

TEST(zero, new_matrix) {
    Matrix m(5), n;
    n = m.zeros(5, 6);
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.cols(), 6);
    EXPECT_EQ(n.coeffRef(0, 2), 0);
}

TEST(identity, new_matrix) {
    Matrix n, m;
    n = m.identity(5, 6);
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.cols(), 6);
    EXPECT_EQ(n.coeffRef(0, 2), 0);
    EXPECT_EQ(n.coeffRef(2, 3), 0);
    EXPECT_EQ(n.coeffRef(4, 5), 0);
    EXPECT_EQ(n.coeffRef(3, 3), 1.0);
    EXPECT_EQ(n.coeffRef(2, 2), 1.0);
}

TEST(constant, new_matrix) {
    Matrix n, m;
    n = m.constants(5, 6, 5.0);
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.cols(), 6);
    EXPECT_EQ(n.coeffRef(0, 2), 5.0);
    EXPECT_EQ(n.coeffRef(4, 5), 5.0);
}

TEST(constant, new_matrix_NAN_value) {
    Matrix m(5), n;
    n = m.constants(5, 6, NAN);
    EXPECT_EQ(n.rows(), 0);
    EXPECT_EQ(n.cols(), 0);
}

TEST(resize, new_matrix) {
    Matrix m(5);
    m.resize(4, 6);
    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 6);

    EXPECT_ANY_THROW(m.coeffRef(25, 4));
    Matrix n(5, 6);
    n.resize(6, 7);
    EXPECT_EQ(n.rows(), 6);
    EXPECT_EQ(n.cols(), 7);
    EXPECT_EQ(n.coeffRef(4, 5), 0);
    EXPECT_EQ(n.coeffRef(5, 5), 0);
    EXPECT_ANY_THROW(n.coeffRef(8, 74));
}

TEST(sum, new_different_matrix) {
    Matrix m(5, 5), n(6, 6), p;
    m.setConstants(5.0);
    n.setConstants(6.1);
    p = m + n;
    EXPECT_EQ(p.cols(), 0);
    EXPECT_EQ(p.rows(), 0);
}

TEST(sum, new_same_matrix) {
    Matrix m(5, 5), n(5, 5), p;
    m.setConstants(5.0);
    n.setConstants(3.0);
    p = m + n;
    EXPECT_EQ(p.cols(), 5);
    EXPECT_EQ(p.rows(), 5);
    EXPECT_EQ(p.coeffRef(1, 1), 8.0);
    EXPECT_EQ(p.coeffRef(4, 4), 8.0);
}

TEST(difference, new_different_matrix) {
    Matrix m(5, 5), n(6, 6), p;
    m.setConstants(5.0);
    n.setConstants(6.1);
    p = m - n;
    EXPECT_EQ(p.cols(), 0);
    EXPECT_EQ(p.rows(), 0);
}

TEST(difference, new_same_matrix) {
    Matrix m(5, 5), n(5, 5), p;
    m.setConstants(5.0);
    n.setConstants(3.0);
    p = m - n;
    EXPECT_EQ(p.cols(), 5);
    EXPECT_EQ(p.rows(), 5);
    EXPECT_EQ(n.coeffRef(1, 1), 3.0);
    EXPECT_EQ(n.coeffRef(4, 4), 3.0);
}

TEST(equality, new_same_matrix) {
    Matrix m(5, 5), n(5, 5);
    m.setConstants(8.0);
    n = m;
    EXPECT_EQ(n.coeffRef(2, 2), m.coeffRef(2, 2));
    EXPECT_EQ(n.coeffRef(3, 4), m.coeffRef(3, 4));
    EXPECT_EQ(m.coeffRef(3, 3), 8.0);
}

TEST(equality, one_matrix) {
    Matrix n(5, 5);
    n.setConstants(8.0);
    n = n;
    EXPECT_EQ(n.coeffRef(2, 2), n.coeffRef(2, 2));
    EXPECT_EQ(n.coeffRef(3, 4), n.coeffRef(3, 4));
}

TEST(equality, new_different_matrix) {
    Matrix m(1, 1), n(4, 4);
    n.setConstants(4.0);
    m = n;
    EXPECT_EQ(m.cols(), 4);
    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(n.coeffRef(2, 2), m.coeffRef(2, 2));
    EXPECT_EQ(n.coeffRef(3, 3), m.coeffRef(3, 3));
    EXPECT_EQ(m.coeffRef(3, 3), 4.0);
}

TEST(value_composition, new_matrix) {
    Matrix m(5, 5), n(5, 5);
    n.setConstants(1.0);
    m = n * 5.0;
    EXPECT_EQ(m.coeffRef(3, 3), 5.0);
    EXPECT_EQ(m.coeffRef(1, 4), 5.0);
}

TEST(value_composition, new_matrix_NAN_value) {
    Matrix m(5, 5), n(5, 5);
    n.setConstants(1.0);
    m = n * NAN;
    EXPECT_EQ(m.cols(), 0);
    EXPECT_EQ(m.rows(), 0);
}

TEST(value_division, new_matrix) {
    Matrix m(5, 5), n(5, 5);
    n.setConstants(5.0);
    m = n / 5.0;
    EXPECT_EQ(m.coeffRef(3, 3), 1.0);
    EXPECT_EQ(m.coeffRef(1, 4), 1.0);
}

TEST(value_division, new_matrix_NAN_value) {
    Matrix m(5, 5), n(5, 5);
    n.setConstants(1.0);
    m = n / NAN;
    EXPECT_EQ(m.cols(), 0);
    EXPECT_EQ(m.rows(), 0);
}

TEST(equality_sum, new_different_matrix) {
    Matrix m(5, 5), n(6, 6);
    m.setConstants(5.0);
    n.setConstants(6.1);
    n += m;
    EXPECT_EQ(n.cols(), 0);
    EXPECT_EQ(n.rows(), 0);
}

TEST(equality_sum, new_same_matrix) {
    Matrix m(5, 5), n(5, 5);
    m.setConstants(5.0);
    n.setConstants(3.0);
    n += m;
    EXPECT_EQ(n.cols(), 5);
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.coeffRef(3, 3), 8.0);
    EXPECT_EQ(n.coeffRef(1, 4), 8.0);
}

TEST(equality_difference, new_different_matrix) {
    Matrix m(5, 5), n(6, 6);
    m.setConstants(5.0);
    n.setConstants(6.0);
    n -= m;
    EXPECT_EQ(n.cols(), 0);
    EXPECT_EQ(n.rows(), 0);
}

TEST(equality_difference, new_same_matrix) {
    Matrix m(5, 5), n(5, 5);
    m.setConstants(5.0);
    n.setConstants(3.0);
    n -= m;
    EXPECT_EQ(n.cols(), 5);
    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.coeffRef(3, 3), -2.0);
    EXPECT_EQ(n.coeffRef(1, 4), -2.0);
}

TEST(equality_value_composition, new_matrix) {
    Matrix n(5, 5);
    n.setConstants(1.0);
    n *= 5.0;
    EXPECT_EQ(n.coeffRef(3, 3), 5.0);
    EXPECT_EQ(n.coeffRef(1, 4), 5.0);
}

TEST(equality_value_composition, new_matrix_NAN_value) {
    Matrix n(5, 5);
    n.setConstants(1.0);
    n *= NAN;
    EXPECT_EQ(n.cols(), 0);
    EXPECT_EQ(n.rows(), 0);
}

TEST(equality_value_composition, new_matrix_INF_value) {
    Matrix n(5, 5);
    n.setConstants(1.0);
    double pos_inf = std::numeric_limits<double>::infinity();
    n *= pos_inf;
    EXPECT_EQ(n.coeffRef(3, 3), pos_inf);
    EXPECT_EQ(n.coeffRef(1, 4), pos_inf);
}

TEST(equality_value_division, new_matrix_INF_value) {
    Matrix n(5, 5);
    n.setConstants(1.0);
    double pos_inf = std::numeric_limits<double>::infinity();
    n /= pos_inf;
    EXPECT_EQ(n.coeffRef(3, 3), 0);
    EXPECT_EQ(n.coeffRef(1, 4), 0);
}

TEST(equality_value_division, new_matrix) {
    Matrix n(5, 5);
    n.setConstants(5.0);
    n /= 5.0;
    EXPECT_EQ(n.coeffRef(3, 3), 1.0);
    EXPECT_EQ(n.coeffRef(1, 4), 1.0);
}

TEST(equality_value_division, new_matrix_NAN_value) {
    Matrix n(5, 5);
    n.setConstants(1.0);
    n /= NAN;
    EXPECT_EQ(n.cols(), 0);
    EXPECT_EQ(n.rows(), 0);
}

TEST(isValid, new_matrix) {
    Matrix n(5, 5);
    n.setConstants(1.0);
    EXPECT_EQ(n.isValid(), true);
}

TEST(friend_value_composition, new_matrix) {
    Matrix m(5, 5), n(5, 5);
    m.setConstants(5.0);
    n = 5.0 * m;
    EXPECT_EQ(n.coeffRef(3, 3), 25.0);
    EXPECT_EQ(n.coeffRef(1, 4), 25.0);
    EXPECT_EQ(n.coeffRef(4, 1), 25.0);
}

TEST(friend_value_composition, new_matrix_NAN_value) {
    Matrix m(5, 5), n(5, 5);
    m.setConstants(5.0);
    n = NAN * m;
    EXPECT_EQ(n.cols(), 0);
    EXPECT_EQ(n.rows(), 0);
}

TEST(friend_value_composition, new_matrix_INF_value) {
    Matrix n(5, 5), m;
    n.setConstants(1.0);
    double pos_inf = std::numeric_limits<double>::infinity();
    m = n * pos_inf;
    EXPECT_EQ(m.coeffRef(3, 3), pos_inf);
    EXPECT_EQ(m.coeffRef(1, 4), pos_inf);
}

TEST(composition, new_different_matrix) {
    Matrix m(5, 5), n(4, 2), p;
    m.setConstants(4.0);
    n.setConstants(3.0);
    p = m * n;
    EXPECT_EQ(p.isValid(), 0);
}

TEST(composition, new_same_matrix) {
    Matrix m(5, 4), n(4, 2), p;
    m.setConstants(4.0);
    n.setConstants(3.0);
    p = m * n;
    EXPECT_EQ(p.cols(), 2);
    EXPECT_EQ(p.rows(), 5);
    EXPECT_EQ(p.coeffRef(3, 1), 48.0);
    EXPECT_EQ(p.coeffRef(1, 1), 48.0);
}

TEST(equality_matrix_composition, new_different_matrix) {
    Matrix m(5, 5), n(4, 2);
    m.setConstants(4.0);
    n.setConstants(3.0);
    m *= n;
    EXPECT_EQ(m.cols(), 0);
    EXPECT_EQ(m.rows(), 0);
}

TEST(equality_matrix_composition, new_same_matrix) {
    Matrix m(5, 4), n(4, 2), p;
    m.setConstants(4.0);
    n.setConstants(3.0);
    m *= n;
    EXPECT_EQ(m.cols(), 2);
    EXPECT_EQ(m.rows(), 5);
    EXPECT_EQ(m.coeffRef(3, 1), 48.0);
    EXPECT_EQ(m.coeffRef(1, 1), 48.0);
}

Matrix setRandom(Matrix m) {
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.rows(); j++)
            m.coeffRef(i, j) = rand() % 10;
    }
    return m;
}

TEST(transpose, new_matrix) {
    Matrix m(4, 4), n(4, 4);
    m.setConstants(5.3);
    n = m;
    m.transpose();
    for (size_t i = 0; i < m.rows(); i++) {
        for (size_t j = 0; j < m.cols(); j++) {
            EXPECT_EQ(m.coeffRef(i, j), n.coeffRef(j, i));
        }
    }

}

TEST(create, zero) {
    Matrix n(0, 0);
    EXPECT_EQ(n.cols(), 0);
    EXPECT_EQ(n.rows(), 0);
    EXPECT_ANY_THROW(n.coeffRef(0, 1));
    EXPECT_ANY_THROW(n.coeffRef(74, 85));
}

TEST(operators, copy2x3) {
    Matrix m1(2, 3);

    m1.coeffRef(0, 0) = 1;
    m1.coeffRef(0, 1) = 0;
    m1.coeffRef(0, 2) = 9;
    m1.coeffRef(1, 0) = 2;
    m1.coeffRef(1, 1) = 3;
    m1.coeffRef(1, 2) = 7;

    Matrix copy = m1;

    EXPECT_EQ(copy.rows(), 2);
    EXPECT_EQ(copy.cols(), 3);

    EXPECT_EQ(copy.coeffRef(0, 0), 1);
    EXPECT_EQ(copy.coeffRef(0, 1), 0);
    EXPECT_EQ(copy.coeffRef(0, 2), 9);
    EXPECT_EQ(copy.coeffRef(1, 0), 2);
    EXPECT_EQ(copy.coeffRef(1, 1), 3);
    EXPECT_EQ(copy.coeffRef(1, 2), 7);
}

TEST(operators, summ2x3) {
    Matrix m1(2, 3);
    Matrix m2(2, 3);

    m1.coeffRef(0, 0) = 1;
    m1.coeffRef(0, 1) = 0;
    m1.coeffRef(0, 2) = 9;
    m1.coeffRef(1, 0) = 2;
    m1.coeffRef(1, 1) = 3;
    m1.coeffRef(1, 2) = 7;

    m2.coeffRef(0, 0) = 2;
    m2.coeffRef(0, 1) = 5;
    m2.coeffRef(0, 2) = 1;
    m2.coeffRef(1, 0) = 0;
    m2.coeffRef(1, 1) = 6;
    m2.coeffRef(1, 2) = 4;

    Matrix summ = m1 + m2;

    EXPECT_EQ(summ.rows(), 2);
    EXPECT_EQ(summ.cols(), 3);

    EXPECT_EQ(summ.coeffRef(0, 0), 3);
    EXPECT_EQ(summ.coeffRef(0, 1), 5);
    EXPECT_EQ(summ.coeffRef(0, 2), 10);
    EXPECT_EQ(summ.coeffRef(1, 0), 2);
    EXPECT_EQ(summ.coeffRef(1, 1), 9);
    EXPECT_EQ(summ.coeffRef(1, 2), 11);
}

TEST(operators, mult2x3) {
    Matrix m1(2, 3);
    Matrix m2(3, 2);
    Matrix m3(2, 3);

    m1.coeffRef(0, 0) = 1;
    m1.coeffRef(0, 1) = 0;
    m1.coeffRef(0, 2) = 9;
    m1.coeffRef(1, 0) = 2;
    m1.coeffRef(1, 1) = 3;
    m1.coeffRef(1, 2) = 7;

    m2.coeffRef(0, 0) = 3;
    m2.coeffRef(0, 1) = 6;
    m2.coeffRef(1, 0) = 8;
    m2.coeffRef(1, 1) = 1;
    m2.coeffRef(2, 0) = 2;
    m2.coeffRef(2, 1) = 4;

    m3.coeffRef(0, 0) = 1;
    m3.coeffRef(0, 1) = 0;
    m3.coeffRef(0, 2) = 9;
    m3.coeffRef(1, 0) = 2;
    m3.coeffRef(1, 1) = 3;
    m3.coeffRef(1, 2) = 7;

    Matrix mult = m1 * m2;
    Matrix invalid_mult = m1 * m3;

    EXPECT_EQ(mult.rows(), 2);
    EXPECT_EQ(mult.cols(), 2);
    EXPECT_FALSE(invalid_mult.isValid());

    EXPECT_EQ(mult.coeffRef(0, 0), 21);
    EXPECT_EQ(mult.coeffRef(0, 1), 42);
    EXPECT_EQ(mult.coeffRef(1, 0), 44);
    EXPECT_EQ(mult.coeffRef(1, 1), 43);
}

TEST(operators, diff2x3) {
    Matrix m1(2, 3);
    Matrix m2(2, 3);

    m1.coeffRef(0, 0) = 1;
    m1.coeffRef(0, 1) = 0;
    m1.coeffRef(0, 2) = 9;
    m1.coeffRef(1, 0) = 2;
    m1.coeffRef(1, 1) = 3;
    m1.coeffRef(1, 2) = 7;

    m2.coeffRef(0, 0) = 2;
    m2.coeffRef(0, 1) = 5;
    m2.coeffRef(0, 2) = 1;
    m2.coeffRef(1, 0) = 0;
    m2.coeffRef(1, 1) = 6;
    m2.coeffRef(1, 2) = 4;

    Matrix diff = m1 - m2;

    EXPECT_EQ(diff.rows(), 2);
    EXPECT_EQ(diff.cols(), 3);

    EXPECT_EQ(diff.coeffRef(0, 0), -1);
    EXPECT_EQ(diff.coeffRef(0, 1), -5);
    EXPECT_EQ(diff.coeffRef(0, 2), 8);
    EXPECT_EQ(diff.coeffRef(1, 0), 2);
    EXPECT_EQ(diff.coeffRef(1, 1), -3);
    EXPECT_EQ(diff.coeffRef(1, 2), 3);
}

TEST(operators, times2x3) {
    Matrix m1(2, 3);

    m1.coeffRef(0, 0) = 1;
    m1.coeffRef(0, 1) = 0;
    m1.coeffRef(0, 2) = 9;
    m1.coeffRef(1, 0) = 2;
    m1.coeffRef(1, 1) = 3;
    m1.coeffRef(1, 2) = 7;

    Matrix times = m1 * 10;

    EXPECT_EQ(times.rows(), 2);
    EXPECT_EQ(times.cols(), 3);

    EXPECT_EQ(times.coeffRef(0, 0), 10);
    EXPECT_EQ(times.coeffRef(0, 1), 0);
    EXPECT_EQ(times.coeffRef(0, 2), 90);
    EXPECT_EQ(times.coeffRef(1, 0), 20);
    EXPECT_EQ(times.coeffRef(1, 1), 30);
    EXPECT_EQ(times.coeffRef(1, 2), 70);
}

TEST(operators, div2x3) {
    Matrix m1(2, 3);

    m1.coeffRef(0, 0) = 1;
    m1.coeffRef(0, 1) = 0;
    m1.coeffRef(0, 2) = 9;
    m1.coeffRef(1, 0) = 2;
    m1.coeffRef(1, 1) = 3;
    m1.coeffRef(1, 2) = 7;

    Matrix div = m1 / 10;

    EXPECT_EQ(div.rows(), 2);
    EXPECT_EQ(div.cols(), 3);

    EXPECT_EQ(div.coeffRef(0, 0), 0.1);
    EXPECT_EQ(div.coeffRef(0, 1), 0);
    EXPECT_EQ(div.coeffRef(0, 2), 0.9);
    EXPECT_EQ(div.coeffRef(1, 0), 0.2);
    EXPECT_EQ(div.coeffRef(1, 1), 0.3);
    EXPECT_EQ(div.coeffRef(1, 2), 0.7);
}

TEST(resize, zero) {
    Matrix n(0, 0);
    EXPECT_EQ(n.rows(), 0);
    EXPECT_EQ(n.cols(), 0);

    n.resize(10, 10);

    EXPECT_EQ(n.rows(), 10);
    EXPECT_EQ(n.cols(), 10);
}

TEST(resize, 2x5to5x5) {
    Matrix n(2, 5);
    EXPECT_EQ(n.rows(), 2);
    EXPECT_EQ(n.cols(), 5);

    n.resize(5, 5);

    EXPECT_EQ(n.rows(), 5);
    EXPECT_EQ(n.cols(), 5);
}

TEST(set, setIdentity) {
    Matrix n(7, 7);
    n.setIdentity();

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            if (i == j)
                EXPECT_EQ(n.coeffRef(i, j), 1);
            else
                EXPECT_EQ(n.coeffRef(i, j), 0);
}


TEST(set, setZero) {
    Matrix n(7, 7);
    n.setZero();

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            EXPECT_EQ(n.coeffRef(i, j), 0);
}

TEST(set, setConstant) {
    Matrix n(7, 7);
    n.setConstants(103);

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            EXPECT_EQ(n.coeffRef(i, j), 103);
}

TEST(transpose, zero) {
    Matrix n(0, 0);
    Matrix res = n.transpose();

    EXPECT_EQ(res.rows(), 0);
    EXPECT_EQ(res.cols(), 0);
}

TEST(transpose, 7x7) {
    Matrix n(7, 7);
    Matrix res = n.setIdentity().transpose();

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            EXPECT_EQ(res.coeffRef(i, j), n.coeffRef(i, j));
}

TEST(inverse, zero) {
    Matrix n(0, 0);
    Matrix res = n.inverse();

    EXPECT_EQ(res.rows(), 0);
    EXPECT_EQ(res.cols(), 0);
}

TEST(inverse, 5x5) {
    Matrix n(5, 5);
    n.setIdentity();
    n *= 2;
    Matrix inv(n.inverse());
    Matrix mult = inv * n;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (i == j)
                EXPECT_EQ(mult.coeffRef(i, j), 1);
            else
                EXPECT_EQ(mult.coeffRef(i, j), 0);
}

TEST(inverse, 7x7) {
    Matrix n(7, 7);
    for (size_t i = 0; i < n.rows(); i++) {
        for (size_t j = 0; j < n.cols(); j++) {
            n.coeffRef(i, j) = i * n.cols() + j;
        }
    }
    Matrix inv(n.inverse());
    EXPECT_EQ(inv.cols(), 0);
    EXPECT_EQ(inv.rows(), 0);
}

TEST(det, zero) {
    Matrix n(0, 0);

    EXPECT_TRUE(std::isnan(n.det()));
}

TEST(det, 4x4) {
    Matrix n(4, 4);
    n.setIdentity();
    n *= 2;

    EXPECT_EQ(n.det(), 16);
}


TEST(det, 1x1) {
    Matrix n(1, 1);
    n.coeffRef(0, 0) = 5;

    EXPECT_EQ(n.det(), 5);
}

TEST(diag, zero) {
    Matrix n(0, 0);
    Matrix d(n.diag());

    EXPECT_EQ(d.rows(), 0);
    EXPECT_EQ(d.cols(), 0);
}

TEST(transpose, 3x3) {
    Matrix n(3, 3);
    n.coeffRef(0, 0) = 1;
    n.coeffRef(0, 1) = 2;
    n.coeffRef(0, 2) = 3;

    n.coeffRef(1, 0) = 5;
    n.coeffRef(1, 1) = 0;
    n.coeffRef(1, 2) = 1;

    n.coeffRef(2, 0) = 0;
    n.coeffRef(2, 1) = 0;
    n.coeffRef(2, 2) = 2;

    Matrix d = n.transpose();

    EXPECT_EQ(d.coeffRef(0, 0), 1);
    EXPECT_EQ(d.coeffRef(0, 1), 5);
    EXPECT_EQ(d.coeffRef(0, 2), 0);
    EXPECT_EQ(d.coeffRef(1, 0), 2);
    EXPECT_EQ(d.coeffRef(1, 1), 0);
    EXPECT_EQ(d.coeffRef(1, 2), 0);
    EXPECT_EQ(d.coeffRef(2, 0), 3);
    EXPECT_EQ(d.coeffRef(2, 1), 1);
    EXPECT_EQ(d.coeffRef(2, 2), 2);
}

TEST(diag, 3x3) {
    Matrix n(3, 3);
    n.coeffRef(0, 0) = 1;
    n.coeffRef(0, 1) = 2;
    n.coeffRef(0, 2) = 3;

    n.coeffRef(1, 0) = 5;
    n.coeffRef(1, 1) = 0;
    n.coeffRef(1, 2) = 1;

    n.coeffRef(2, 0) = 0;
    n.coeffRef(2, 1) = 0;
    n.coeffRef(2, 2) = 2;

    Matrix d = n.diag();

    EXPECT_EQ(d.coeffRef(0, 0), 1);
    EXPECT_EQ(d.coeffRef(0, 1), 0);
    EXPECT_EQ(d.coeffRef(0, 2), 0);
    EXPECT_EQ(d.coeffRef(1, 0), 0);
    EXPECT_EQ(d.coeffRef(1, 1), -10);
    EXPECT_EQ(d.coeffRef(1, 2), 0);
    EXPECT_EQ(d.coeffRef(2, 0), 0);
    EXPECT_EQ(d.coeffRef(2, 1), 0);
    EXPECT_EQ(d.coeffRef(2, 2), 2);
}
