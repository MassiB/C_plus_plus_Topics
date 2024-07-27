/**
 * @file MatrixView.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "MatrixView.hpp"

#include <iostream>

namespace
{
#define SPACE " ";
} // anonymous namespace

/// @brief display matrix content into the console
/// @param mat 
/// @return void
auto MatrixView::show(const Matrix &mat) -> void
{
    std::lock_guard<std::mutex> lock(m_mtx);
    auto row = mat.getDimension().first;
    auto col = mat.getDimension().second;
    for (unsigned int r(1); r <= row; ++r) {
        for (unsigned int c(1); c <= col; ++c){
            std::cout << mat.getValue(r,c) << SPACE;
        }
        std::cout << std::endl;
    }    
}
