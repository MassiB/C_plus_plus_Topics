/**
 * @file Ressource.hpp
 * @author Massinissa
 * @brief 
 * @version 0.1
 * @date 2024-07-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef RESSOURCE_HPP_
#define RESSOURCE_HPP_

#include "Utilities.hpp"

#include <mutex>

/// @brief class to handle safe thread ressources
/// @tparam Ressource 
template <typename Ressource>
class ThreadSafeRessource
{
public:
    explicit ThreadSafeRessource(Ressource *res);
    virtual ~ThreadSafeRessource();

    auto lock() -> void;
    auto unlock() -> void;
    auto try_lock() -> bool;
    auto getMutex() -> std::mutex&;
    template <typename T>
    auto getRessource(std::unique_lock<T>& lock) -> Ressource*;
private:
    std::mutex m_mtx;
    Ressource *m_ressource {nullptr};
};

/// @brief constructor
/// @tparam Ressource 
/// @param res 
template <typename Ressource>
ThreadSafeRessource<Ressource>::ThreadSafeRessource(Ressource *res) : m_ressource(res) 
{}

/// @brief destructor
/// @tparam Ressource 
template <typename Ressource>
ThreadSafeRessource<Ressource>::~ThreadSafeRessource()
{}

/// @brief lock mutex
/// @tparam Ressource 
/// @return void
template <typename Ressource>
auto ThreadSafeRessource<Ressource>::lock() -> void
{
    m_mtx.lock();
}

/// @brief unlock mutex
/// @tparam Ressource 
/// @return void
template <typename Ressource>
auto ThreadSafeRessource<Ressource>::unlock() -> void
{
    m_mtx.unlock();
}

/// @brief try to lock mutex
/// @tparam Ressource 
/// @return bool
template <typename Ressource>
auto ThreadSafeRessource<Ressource>::try_lock() -> bool
{
    return m_mtx.try_lock();
}

/// @brief get current mutex
/// @tparam Ressource 
/// @return std::mutex&
template <typename Ressource>
auto ThreadSafeRessource<Ressource>::getMutex() -> std::mutex&
{
    return m_mtx;
}

/// @brief get current ressource
/// @tparam Ressource 
/// @param lock 
/// @return Ressource*
template <typename Ressource>
template <typename T>
auto ThreadSafeRessource<Ressource>::getRessource(typename std::unique_lock<T>& lock) -> Ressource*
{
    unused(lock);
    return m_ressource;
}

#endif /*RESSOURCE_HPP_*/
