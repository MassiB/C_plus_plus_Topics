/**
 * @file Scheduler.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SCHEDULER_HPP_
#define SCHEDULER_HPP_

#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <stack>

/// @brief Scheduler class act like a task manager
class Scheduler
{
    typedef std::function<void()> TASK;
    enum STATE {
        STOP,
        START
    };
public:
    Scheduler();
    virtual ~Scheduler();

    Scheduler(const Scheduler &) = delete;
    Scheduler& operator=(const Scheduler &) = delete;

    auto start() -> void;
    auto stop() -> void;

    template <typename FUNC, typename... ARGS>
    auto schedule(long timeschedule, FUNC && func, ARGS &&... args) -> void;
private:
    std::atomic<STATE> m_running {STOP};
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::stack<std::pair<long,TASK>> m_stack;

    auto round_robin_execution() -> void;
};

/// @brief Function to add task into the queue
/// @tparam FUNC 
/// @tparam ...ARGS 
/// @param timeschedule 
/// @param func 
/// @param ...args 
/// @return void
template <typename FUNC, typename... ARGS>
auto Scheduler::schedule(long timeschedule, FUNC && func, ARGS &&... args) -> void
{
    std::unique_lock<std::mutex> lock(m_mtx);
    auto task = std::bind(std::forward<FUNC>(func), std::forward<ARGS>(args)...);
    m_stack.push(std::make_pair(timeschedule, [&]()->void{ task(); }));
}

#endif /*SCHEDULER_HPP_*/
