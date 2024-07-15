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
#include <memory>
#include <mutex>
#include <optional>

/// @brief Queue class
/// @tparam DataType 
template <typename DataType>
class Queue
{
    struct InternalStructure final
    {
        InternalStructure(const DataType & data);
        ~InternalStructure() = default;
        std::unique_ptr<InternalStructure> next {nullptr};
        DataType data;
    };
    typedef InternalStructure Node;
public:
    Queue() = default;
    virtual ~Queue() = default;
    auto push(const DataType & data) -> void;
    auto pop() -> void;
    auto front() -> std::optional<DataType>;
    auto empty() -> bool;
private:
    std::unique_ptr<Node> m_head {nullptr};
    Node *m_tail {nullptr};
    std::mutex m_mtx;
    std::condition_variable m_cv;
};

/// @brief constructor 
/// @tparam DataType 
/// @param _data 
template <typename DataType>
Queue<DataType>::InternalStructure::InternalStructure(const DataType & _data) : data(_data)
{}

/// @brief insert data into the queue
/// @tparam DataType 
/// @param data 
/// @return void
template <typename DataType>
auto Queue<DataType>::push(const DataType & data) -> void
{
    std::lock_guard<std::mutex> lock(m_mtx);
    auto newNode = std::make_unique<Node> (data);
    if (nullptr == m_head){
        m_head = std::move(newNode);
        m_tail = m_head.get();
        return;
    }
    m_tail->next = std::move(newNode);
    m_tail = m_tail->next.get();
    m_cv.notify_one();
}

/// @brief remove first element of the queue
/// @tparam DataType 
/// @return void
template <typename DataType>
auto Queue<DataType>::pop() -> void
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this]()->bool {return m_head != nullptr;});
    if (m_head.get() == m_tail) {
        m_head.reset(nullptr);
        m_tail = nullptr;
    } else {
        m_head = std::move(m_head->next);
    }
}

/// @brief return first element of the queue
/// @tparam DataType 
/// @return std::optional<DataType>
template <typename DataType>
auto Queue<DataType>::front() -> std::optional<DataType>
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this]() -> bool {return m_head != nullptr;});
    return (nullptr != m_head) ? std::optional<DataType> {m_head->data} :
        std::nullopt;
}

/// @brief return true if queue is empty otherwise false
/// @tparam DataType 
/// @return bool
template <typename DataType>
auto Queue<DataType>::empty() -> bool
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_head == nullptr;
}

#endif /*QUEUE_HPP_*/
