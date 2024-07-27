/**
 * @file Matrix.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <utility>

/// @brief Matrix class
class Matrix
{
    typedef std::pair<int,int> DIMENSION;
public:
    Matrix(int _row, int _col);
    virtual ~Matrix();
    Matrix(const Matrix &mat);
    Matrix& operator=(const Matrix &mat);
    /*setters/getters*/
    auto setValue(int _row, int _col, int val) noexcept(false) -> void;
    auto getValue(int _row, int _col) const noexcept(false) -> int;
    auto setAll(int val) -> void;
    auto isSquared() const -> bool;
    auto getDimension() const -> DIMENSION;
private:
    int m_row {0}, m_col {0};
    std::unique_ptr<int[]> m_data {nullptr};
    mutable std::mutex m_mtx;
    std::condition_variable m_cv;
};

#endif /*MATRIX_HPP*/
