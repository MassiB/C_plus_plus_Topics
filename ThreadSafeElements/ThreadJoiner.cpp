/**
 * @file ThreadJoiner.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ThreadJoiner.hpp"

/// @brief constructor
/// @param threads 
ThreadJoiner::ThreadJoiner(std::vector<std::thread> & threads) : m_threads(std::move(threads)) 
{}

/// @brief destructor
ThreadJoiner::~ThreadJoiner()
{
    for (auto &t : m_threads)
        if (t.joinable())
            t.join(); 
}
