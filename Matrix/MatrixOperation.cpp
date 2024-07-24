/**
 * @file MatrixOperation.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "MatrixOperation.hpp"

#include <stdexcept>

/// @brief Perform matrix multiplication
/// @param mat1 
/// @param mat2 
/// @return Matrix
auto MatrixOperation::mult(const Matrix &mat1, const Matrix &mat2) noexcept(false) -> Matrix
{
    auto col2 = mat2.getDimension().second;
    auto row2 = mat2.getDimension().first;
    auto col1 = mat1.getDimension().second;
    auto row1 = mat1.getDimension().first;
    if (row2 != col1)
        throw std::out_of_range("Matrix 1 col should be equal to matrix 2 row");
    Matrix resulted_matrix(row1, col2);
    const int size = row1 * col2;
    for (unsigned int lr(0); lr < row1; ++lr)
    {
        int value = 0; int lstart = lr * col1;
        for (unsigned int rc(0); rc < col2; ++rc)
        {
            int rstart = rc * col2;
            for (unsigned int l(lstart), r(rstart);
                l < (lstart + col1) && r < (rstart + row2);
                    ++l, ++r) {
                value += mat1.getValue(lr,l) * mat2.getValue(r,rc);
            }
            resulted_matrix.setValue(lr + 1, rc + 1, value);
        }
    }
    return {resulted_matrix};
}

/// @brief Perform matrix addition
/// @param mat1 
/// @param mat2 
/// @return Matrix
auto MatrixOperation::add(const Matrix &mat1, const Matrix &mat2) noexcept(false) -> Matrix
{
    if (mat1.getDimension() != mat2.getDimension())
        throw std::out_of_range("Matrices should have same dimension");
    const int row(mat1.getDimension().first), col(mat2.getDimension().second);    
    Matrix mat(row, col);
    const int size = row * col;
    for (unsigned int r(1); r <= row; ++r)
        for (unsigned int c(1); c <= col; ++c)
            mat.setValue(r,c, mat1.getValue(r,c) + mat2.getValue(r,c)); 
    return mat;
}

/// @brief Perform matrix substraction
/// @param mat1 
/// @param mat2 
/// @return Matrix
auto MatrixOperation::sub(const Matrix &mat1, const Matrix &mat2) noexcept(false) -> Matrix
{
    if (mat1.getDimension() != mat2.getDimension())
        throw std::out_of_range("Matrices should have same dimension");
    const int row(mat1.getDimension().first), col(mat2.getDimension().second);    
    Matrix mat(row, col);
    const int size = row * col;
    for (unsigned int r(1); r <= row; ++r)
        for (unsigned int c(1); c <= col; ++c)
            mat.setValue(r,c, mat1.getValue(r,c) - mat2.getValue(r,c)); 
    return mat;
}
