/**
 * @file ThreadJoiner.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef THREADJOINER_HPP_
#define THREADJOINER_HPP_

#include <vector>
#include <thread>

/// @brief threadjoiner class 
class ThreadJoiner
{
public:
    explicit ThreadJoiner(std::vector<std::thread> & threads);
    virtual ~ThreadJoiner();
private:
    std::vector<std::thread> m_threads;
};

#endif /*THREADJOINER_HPP_*/
