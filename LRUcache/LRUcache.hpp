/**
 * @file LRUcache.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LRUCACHE_HPP_
#define LRUCACHE_HPP_

#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <stdexcept>

namespace
{
    constexpr static int EMPTY = 0;
}; /*anonymous namespace*/

/// @brief template class of LRU cache
/// @tparam KEY 
/// @tparam VALUE 
template <typename KEY, typename VALUE>
class LRUcache
{
    typedef std::pair<KEY,VALUE> PAIR;
public:
    explicit LRUcache(std::size_t size);
    virtual ~LRUcache() = default;

    auto get(const KEY & key) noexcept(false) -> VALUE&;
    auto insert(KEY && key , VALUE && value) -> void;
    auto print_to_console() const -> void;
private:
    std::size_t m_size {EMPTY};
    std::list<PAIR> m_list;
    std::unordered_map<KEY, typename std::list<PAIR>::iterator> m_umap;
};

/// @brief constructor
/// @tparam KEY 
/// @tparam VALUE 
/// @param size 
template <typename KEY, typename VALUE>
LRUcache<KEY,VALUE>::LRUcache(std::size_t size) : m_size(size)
{}

/// @brief 
/// @tparam KEY 
/// @tparam VALUE 
/// @param key 
/// @return VALUE&
template <typename KEY, typename VALUE>
auto LRUcache<KEY,VALUE>::get(const KEY &key) noexcept(false) -> VALUE&
{
    if (m_umap.find(key) == m_umap.end())
        throw std::bad_alloc();
    return m_umap[key]->second;
}

/// @brief insert key/value into the cache 
/// @tparam KEY 
/// @tparam VALUE 
/// @param pair 
/// @return void
template <typename KEY, typename VALUE>
auto LRUcache<KEY,VALUE>::insert(KEY && key , VALUE && value) -> void
{
    auto current_size = m_list.size();
    auto found = m_umap.find(key);
    if (found != m_umap.end()) {
        found->second->second = std::move(value);
        m_list.splice(m_list.begin(), m_list, found->second);
    } else {
        if (current_size == m_size) {
            m_list.pop_back();
            auto back = m_umap.find(m_list.back().first);
            m_umap.erase(back);
        }
        m_list.push_front(std::make_pair(key,value));
        m_umap.insert(std::make_pair(key,m_list.begin()));
    }
}

/// @brief function to print in a console
/// @tparam KEY 
/// @tparam VALUE 
/// @return void
template <typename KEY, typename VALUE>
auto LRUcache<KEY,VALUE>::print_to_console() const -> void
{
    for (auto &l : m_list)
        std::cout << "key: " << l.first <<
                     " value: " << l.second << std::endl;
}

#endif /*LRUCACHE_HPP_*/
