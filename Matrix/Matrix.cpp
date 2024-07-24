/**
 * @file Matrix.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Matrix.hpp"
#include "Logger/Logger.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

/// @brief constructor
/// @param _row 
/// @param _col 
Matrix::Matrix(int _row, int _col) : m_row(_row), m_col(_col)
{
    m_data = std::make_unique<int[]>(m_row * m_col);
    setAll(0);
}

/// @brief copy constructor
/// @param mat 
Matrix::Matrix(const Matrix &mat)
{
    if (this != &mat) {
        std::lock_guard<std::mutex> lock(m_mtx, std::adopt_lock);
        m_data.reset(nullptr);
        m_col = mat.m_col;
        m_row = mat.m_row;
        m_data = std::make_unique<int[]>(m_row*m_col);
        for (unsigned int i(0); i < m_row*m_col; ++i)
            m_data.get()[i] = mat.m_data.get()[i];
    }
}

/// @brief copy assignment
/// @param mat 
/// @return Matrix&
Matrix& Matrix::operator=(const Matrix &mat)
{
    if (this != &mat)
    {
        std::unique_lock<std::mutex> lock1(m_mtx, std::defer_lock);
        std::unique_lock<std::mutex> lock2(mat.m_mtx, std::defer_lock);
        m_data.reset(nullptr);
        m_col = mat.m_col;
        m_row = mat.m_row;
        m_data = std::make_unique<int[]>(m_row*m_col);
        for (unsigned int i(0); i < m_row*m_col; ++i)
            m_data.get()[i] = mat.m_data.get()[i];
    }
    return *this;
}

/// @brief destructor
Matrix::~Matrix()
{}

/// @brief set matrix row/col value
/// @param _row 
/// @param _col 
/// @param val 
/// @return void
auto Matrix::setValue(int _row, int _col, int val) -> void
{
    if (_row > m_row || _row < 0 || _col > m_col || _col < 0) 
        throw std::out_of_range ("Matrix position is out of range!");
    int val_index = (_row - 1) * m_col + (_col - 1);
    m_data.get()[val_index] = val;
}

/// @brief get row/col value
/// @param _row 
/// @param _col 
/// @return int
auto Matrix::getValue(int _row, int _col) const -> int
{
    if (_row > m_row || _row < 0 || _col > m_col || _col < 0) 
        throw std::out_of_range ("Matrix position is out of range!");
    return m_data.get()[(_row - 1) * m_row + _col];
}

/// @brief set all matrix value to val
/// @param val 
/// @return void
auto Matrix::setAll(int val) -> void
{
    for (unsigned int i(0); i < m_row * m_col; ++i) {
        m_data.get()[i] = val;
    }
}

/// @brief retur true if matrix is squared otherwise false
/// @return bool
auto Matrix::isSquared() const -> bool
{
    return m_row == m_col;
}

/// @brief return matrix dimension
/// @return DIMENSION
auto Matrix::getDimension() const -> DIMENSION
{
    return std::make_pair(m_row, m_col);
}

/// @brief display the matrix to the console
/// @return void
auto Matrix::display() const -> void
{
    for (unsigned int row(0); row < m_row; ++row) {
        for (unsigned int col(0); col < m_col; ++col) {
            std::cout << m_data.get()[row * m_col + col] << " ";
        }
        std::cout << '\n';
    }
}
