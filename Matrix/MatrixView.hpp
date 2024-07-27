/**
 * @file MatrixView.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef MATRIXVIEW_HPP_
#define MATRIXVIEW_HPP_

#include "Matrix.hpp"

#include <mutex>

/// @brief Matrix view class
class MatrixView
{
public:
    MatrixView() = default;
    virtual ~MatrixView() = default;
    static auto show(const Matrix &mat) -> void;
private:
    inline static std::mutex m_mtx;
};

#endif /*MATRIXVIEW_HPP_*/
