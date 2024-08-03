/**
 * @file Log.hpp
 * @author Massinissa BAndou
 * @brief 
 * @version 0.1
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LOG_HPP_
#define LOG_HPP_

#include "Logger.hpp"

/// Defines logging verbosity
#define LOG_DEBUG(...) Logger::getInstance()->log(LEVEL::LEVEL_DEBUG,  __VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance()->log(LEVEL::LEVEL_ERROR, __VA_ARGS__)
#define LOG_INFO(...) Logger::getInstance()->log(LEVEL::LEVEL_INFO, __VA_ARGS__)
#define LOG_WARNING(...) Logger::getInstance()->log(LEVEL::LEVEL_WARNING, __VA_ARGS__)
#define LOG_CRITICAL(...) Logger::getInstance()->log(LEVEL::LEVEL_CRITICAL, __VA_ARGS__)

#endif /// LOG_HPP_
