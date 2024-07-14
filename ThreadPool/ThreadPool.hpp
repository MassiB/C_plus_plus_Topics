/**
 * @file ThreadPool.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <vector>
#include <queue>
#include <thread>

/// @brief ThreadPool class
class ThreadPool final
{
    typedef std::function<void()> TASK;
    auto execute() -> void;
public:
    explicit ThreadPool(std::size_t numThreads);
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template <typename Func, typename ...Args>
    auto addTask(Func && func, Args&&... args) -> void;
private:
    std::atomic<bool> m_running;
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::vector<std::thread> m_threads;
    std::queue<TASK> m_queue;
};

/// @brief Add any task to the queue
/// @tparam Func 
/// @tparam ...Args 
/// @param func 
/// @param ...args 
/// @return void
template <typename Func, typename ...Args>
auto ThreadPool::addTask(Func && func, Args&&... args) -> void
{
    std::unique_lock<std::mutex> lock(m_mtx);
    auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
    m_queue.push(std::move(task));
    m_cv.notify_one();
}

#endif /*THREADPOOL_HPP_*/
