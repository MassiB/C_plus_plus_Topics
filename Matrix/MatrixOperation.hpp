/**
 * @file MatrixOperation.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef MATRIXOPERATION_HPP_
#define MATRIXOPERATION_HPP_

#include "Matrix.hpp"

/// @brief Matrix operation class
class MatrixOperation
{
public:
    MatrixOperation() = default;
    virtual ~MatrixOperation() = default;
    static auto mult(const Matrix &mat1, const Matrix &mat2) noexcept(false) -> Matrix;
    static auto add(const Matrix &mat1, const Matrix &mat2) noexcept(false) -> Matrix;
    static auto sub(const Matrix &mat1, const Matrix &mat2) noexcept(false) -> Matrix;
};

#endif /*MATRIXOPERATION_HPP_*/
