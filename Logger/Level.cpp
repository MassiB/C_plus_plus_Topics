/**
 * @file Level.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Level.hpp"

/// @brief conver level to string equivalant.
/// @param level 
/// @return std::string
auto convert_level_to_string(LEVEL level) -> std::string
{
    switch (level)
    {
        default:
        case LEVEL::LEVEL_DEBUG:
            return "[DEBUG]";
        case LEVEL::LEVEL_INFO:
            return "[INFO]";
        case LEVEL::LEVEL_WARNING:
            return "[WARNING]";
        case LEVEL::LEVEL_CRITICAL:
            return "[CRITICAL]";
        case LEVEL::LEVEL_ERROR:
            return "[ERROR]";
    };
    return {};
}
