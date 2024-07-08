/**
 * @file ThreadPool.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ThreadPool.hpp"

/// @brief Constructor
/// @param numThreads 
ThreadPool::ThreadPool(std::size_t numThreads) : m_running(true)
{
    for (unsigned int i(0); i < numThreads; ++i)
        m_threads.emplace_back(
            std::thread(&ThreadPool::execute, this));
}

/// @brief Destructor
ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_running.store(false);
        m_cv.notify_all();
    }
    for (auto &t : m_threads)
        if (t.joinable())
            t.join();
}

/// @brief execute function by each thread
/// @return void
auto ThreadPool::execute() -> void
{
    for (;;)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [this]() -> bool { return !m_running.load() || !m_queue.empty(); });
        if (!m_running.load())
            break; 
        auto task = std::move(m_queue.front());
        m_queue.pop();
        /**execute task**/
        task();
    }
}
