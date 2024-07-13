/**
 * @file Stack.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef STACK_HPP_
#define STACK_HPP_

#include <condition_variable>
#include <memory>
#include <mutex>

/// @brief Stack class
/// @tparam DataType 
template <typename DataType>
class Stack
{
    struct InternalStructure
    {
        InternalStructure(const DataType & _data) : data(_data) {}
        std::unique_ptr<InternalStructure> next {nullptr};
        DataType data;
    };
    typedef InternalStructure Node;
public:
    Stack() = default;
    virtual ~Stack() = default;
    
    auto push(const DataType & element) -> void;
    auto top() -> DataType&;
    auto pop() -> void;
    auto empty() -> bool;
private:
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::unique_ptr<Node> m_head {nullptr};
};

/// @brief push element to the stack
/// @tparam DataType 
/// @param element 
/// @return void
template <typename DataType>
auto Stack<DataType>::push(const DataType & element) -> void
{
    std::lock_guard<std::mutex> lock(m_mtx);
    auto newNode = std::make_unique<Node>(element);
    newNode->next = std::move(m_head);
    m_head = std::move(newNode);
    m_cv.notify_one();
}

/// @brief return first element of the stack
/// @tparam DataType 
/// @return DataType&
template <typename DataType>
auto Stack<DataType>::top() -> DataType&
{
    std::lock_guard<std::mutex> lock(m_mtx);
    if (nullptr == m_head) 
        throw std::bad_alloc();
    return m_head->data;
}

/// @brief remove top element of the stack
/// @tparam DataType 
/// @return void
template <typename DataType>
auto Stack<DataType>::pop() -> void
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this]() -> bool { return m_head != nullptr; });
    auto ref = std::move(m_head->next);
    m_head.reset(nullptr);
    m_head = std::move(ref);
}

/// @brief return true is stack is empty otherwise false
/// @tparam DataType 
/// @return bool
template <typename DataType>
auto Stack<DataType>::empty() -> bool
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_head == nullptr;
}

#endif /*STACK_HPP_*/
