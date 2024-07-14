/**
 * @file Queue.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <condition_variable>
#include <queue>
#include <memory>
#include <mutex>

/// @brief Thread safe container
/// @tparam DataType 
template <typename DataType>
class Queue
{
public:
    Queue() = default;
    virtual ~Queue() = default;
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue(Queue&&) = default;
    Queue& operator=(Queue&&) = default;

    auto push(const DataType & element) -> void;
    auto pop(DataType & element) -> void;
    auto empty() const -> bool;
    auto size() -> std::size_t;
private:
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::queue<std::shared_ptr<DataType>> m_queue;
};

/// @brief push element to m_queue
/// @tparam DataType 
/// @param element 
/// @return void
template <typename DataType>
auto Queue<DataType>::push(const DataType & element) -> void
{
    std::lock_guard<std::mutex> lock(m_mtx);
    m_queue.push(std::make_shared<DataType>(elements));
    m_cv.notify_one();
}

/// @brief remove first element of m_queue
/// @tparam DataType 
/// @param element 
/// @return void
template <typename DataType>
auto Queue<DataType>::pop(DataType & element) -> void
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this]() -> bool { return !m_queue.empty(); });
    if (m_queue.empty()) return;
    element = *m_queue.front().get();
    m_queue.pop();
}

/// @brief return if m_queue is empty or not
/// @tparam DataType 
/// @return bool
template <typename DataType>
auto Queue<DataType>::empty() const -> bool
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.empty();
}

/// @brief get the size of m_queue
/// @tparam DataType 
/// @return std::size_t
template <typename DataType>
auto Queue<DataType>::size() -> std::size_t
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_queue.size();
}

#endif /*QUEUE_HPP_*/
