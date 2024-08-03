/**
 * @file Level.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <string>

/// @brief verbosity level
enum class LEVEL
{
    LEVEL_DEBUG,
    LEVEL_ERROR,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_CRITICAL
};

auto convert_level_to_string(LEVEL level) -> std::string;

#endif /// LEVEL_HPP_
