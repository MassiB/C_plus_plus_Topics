/**
 * @file Scheduler.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Scheduler.hpp"

/// @brief constructor
Scheduler::Scheduler()
{}

/// @brief destructor
Scheduler::~Scheduler()
{}

/// @brief start scheduler
/// @return void
auto Scheduler::stop() -> void
{
    m_running.store(STOP);
    m_cv.notify_all();
}

/// @brief stop scheduler
/// @return void
auto Scheduler::start() -> void
{
    m_running.store(START);
    round_robin_execution();
    m_cv.notify_one();
}

/// @brief 
/// @return void
auto Scheduler::round_robin_execution() -> void
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this]() -> bool 
            { return m_running.load() == START; });
    while (!m_stack.empty())
    {
        auto task = std::move(m_stack.top());
        m_stack.pop();
        std::thread(task.second).detach();
        std::this_thread::sleep_for(std::chrono::seconds(task.first));
    }
}
