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
    auto col1 = mat1.getDimension().second;
    auto row1 = mat1.getDimension().first;
    auto col2 = mat2.getDimension().second;
    auto row2 = mat2.getDimension().first;
    if (row2 != col1)
        throw std::out_of_range(std::string(__FUNCTION__) + ": Matrix 1 col should be equal to matrix 2 row");
    Matrix resulted_matrix(row1, col2);
    for (unsigned int mat1row(1); mat1row <= row1; ++mat1row) {
        int mat1_start = (mat1row == 1) ? 1 : (mat1row - 1) * col1;
        for (unsigned int mat2col(1); mat2col <= col2; ++mat2col) {
            int value = 0;
            for (unsigned int i(mat1_start); i <= col1; ++i) {
                value += mat1.getValue(mat1_start, i) * mat2.getValue(i, mat2col);
            }
            resulted_matrix.setValue(mat1row, mat2col, value);
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
        throw std::out_of_range(std::string(__FUNCTION__) + ": Matrices should have same dimension");
    const int row(mat1.getDimension().first), col(mat1.getDimension().second);    
    Matrix mat(row, col);
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
        throw std::out_of_range(std::string(__FUNCTION__) + ": Matrices should have same dimension");
    const int row(mat1.getDimension().first), col(mat2.getDimension().second);    
    Matrix mat(row, col);
    for (unsigned int r(1); r <= row; ++r)
        for (unsigned int c(1); c <= col; ++c)
            mat.setValue(r,c, mat1.getValue(r,c) - mat2.getValue(r,c)); 
    return mat;
}
