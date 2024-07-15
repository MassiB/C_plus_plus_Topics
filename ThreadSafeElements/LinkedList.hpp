/**
 * @file LinkedList.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <optional>

/// @brief Linked List class
/// @tparam DataType 
template <typename DataType>
class LinkedList
{
    struct InternalStructure final
    {
        InternalStructure(const DataType &_data) : data(_data) {}
        ~InternalStructure() = default;
        std::unique_ptr<InternalStructure> next {nullptr};
        InternalStructure *prev {nullptr};
        DataType data;
    };
public:
    struct InternalIterator final
    {
        InternalIterator() = default;
        ~InternalIterator() = default;
        InternalIterator& operator++();
        DataType& operator*();
        InternalStructure *operator->();
        bool operator!=(const InternalIterator&);
        bool operator==(const InternalIterator&);
        InternalStructure *current {nullptr};
    };
protected:
    typedef InternalStructure Node;
    typedef InternalIterator Iterator;
public:
    LinkedList() = default;
    virtual ~LinkedList() = default;
    auto push_back(const DataType & element) -> void;
    auto push_front(const DataType & element) -> void;
    auto pop_front() -> void;
    auto pop_back() -> void;
    auto empty() -> bool;
    auto front() -> std::optional<DataType>;
    auto back() -> std::optional<DataType>;
    auto begin() -> Iterator&;
    auto end() -> Iterator&;
private:
    std::unique_ptr<Node> m_head {nullptr};
    Node *m_tail {nullptr};
    Iterator m_itr;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};

/// @brief push element to the linked list
/// @tparam DataType 
/// @param element 
/// @return void
template <typename DataType>
auto LinkedList<DataType>::push_back(const DataType & element) -> void
{
    std::lock_guard<std::mutex> lock(m_mtx);
    auto newNode = std::make_unique<Node>(element);
    newNode->prev = m_tail;
    if (nullptr == m_head) {
        m_head = std::move(newNode);
        m_tail = m_head.get();
        return;
    }
    m_tail->next = std::move(newNode);
    m_tail = m_tail->next.get();
    m_cv.notify_one();
}

/// @brief push element to the head of the linked list
/// @tparam DataType 
/// @param element 
/// @return void
template <typename DataType>
auto LinkedList<DataType>::push_front(const DataType & element) -> void
{
    std::lock_guard<std::mutex> lock(m_mtx);
    auto newNode = std::make_unique<Node>(element);
    if (nullptr == m_head){
        m_head = std::move(newNode);
        m_tail = m_head.get();
    } else {
        newNode->next = std::move(m_head);
        m_head = std::move(newNode);
    }
    m_cv.notify_one();
}

/// @brief remove first element of the linkedlist
/// @tparam DataType 
/// @return void
template <typename DataType>
auto LinkedList<DataType>::pop_front() -> void
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this]() -> bool { return m_head != nullptr; });
    if (m_tail == m_head.get()) {
        m_head.reset(nullptr);
        m_tail = nullptr;
        return;
    }
    auto next = std::move(m_head->next);
    m_head.reset(nullptr);
    m_head = std::move(next);
    m_head->prev = nullptr;
}

/// @brief remove last element of the linkedlist
/// @tparam DataType 
/// @return void
template <typename DataType>
auto LinkedList<DataType>::pop_back() -> void
{
    std::lock_guard<std::mutex> lock(m_mtx);
    if (nullptr == m_head) return;
    if (m_tail == m_head.get()) {
        m_head.reset(nullptr);
        return;
    }
    auto prev = m_tail->prev;
    prev->next.reset(nullptr);
    m_tail = prev;
}

/// @brief return true if linkedlist is empty
/// @tparam DataType 
/// @return bool
template <typename DataType>
auto LinkedList<DataType>::empty() -> bool
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_head == nullptr;
}

/// @brief return first element of the linked list
/// @tparam DataType 
/// @return std::optional<DataType>
template <typename DataType>
auto LinkedList<DataType>::front() -> std::optional<DataType>
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return (nullptr != m_head) ? std::optional<DataType> {m_head->data} :
        std::nullopt;
}

/// @brief return last element of the linked list
/// @tparam DataType 
/// @return std::optional<DataType>
template <typename DataType>
auto LinkedList<DataType>::back() -> std::optional<DataType>
{
    std::lock_guard<std::mutex> lock(m_mtx);
    return (nullptr != m_tail) ? std::optional<DataType> {m_tail->data} :
        std::nullopt;
}

/// @brief return iterator at the beginning of the list
/// @tparam DataType 
/// @return Iterator&
template <typename DataType>
auto LinkedList<DataType>::begin() -> Iterator&
{
    std::lock_guard<std::mutex> lock(m_mtx);
    m_itr.current = m_head.get();
    return m_itr;
}

/// @brief return last element of the linked list
/// @tparam DataType 
/// @return Iterator&
template <typename DataType>
auto LinkedList<DataType>::end() -> Iterator&
{
    std::lock_guard<std::mutex> lock(m_mtx);
    Iterator itr;
    itr.current = nullptr;  // End iterator points to nullptr
    return itr;
}

/// @brief incremental operator
/// @tparam DataType 
/// @return Iterator&
template <typename DataType>
typename LinkedList<DataType>::Iterator& LinkedList<DataType>::Iterator::operator++()
{
    if (nullptr != current)
        current = current->next.get();
    return *this;
}

/// @brief * operator
/// @tparam DataType 
/// @return DataType&
template <typename DataType>
DataType& LinkedList<DataType>::Iterator::operator*()
{
    return current->data;
}

/// @brief dereference operator
/// @tparam DataType 
/// @return Node*
template <typename DataType>
typename LinkedList<DataType>::Node* LinkedList<DataType>::Iterator::operator->()
{
    return current;
}

/// @brief true of iterator are same otherwise false
/// @tparam DataType 
/// @param itr 
/// @return bool
template <typename DataType>
bool LinkedList<DataType>::Iterator::operator!=(const Iterator & itr)
{
    return current != itr.current;
}

/// @brief true of iterator are same otherwise false
/// @tparam DataType 
/// @param itr 
/// @return bool
template <typename DataType>
bool LinkedList<DataType>::Iterator::operator==(const Iterator & itr)
{
    return !operator!=(itr);
}

#endif /*LINKEDLIST_HPP_*/
