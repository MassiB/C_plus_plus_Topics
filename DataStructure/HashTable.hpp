/**
 * @file HashTable.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include <algorithm>
#include <vector>
#include <list>
#include <utility>
#include <mutex>
#include <iostream>
#include <thread>
#include <stdexcept>

/// @brief HashTable class
/// @tparam DataType 
template<typename DataType>
class HashTable
{
    constexpr static int BUCKET_SIZE {16};
public:
    HashTable() : m_table(BUCKET_SIZE) {}
    virtual ~HashTable() = default;
    auto insert (const int key, const DataType & data) -> void;
    auto get(const int key) noexcept(false) -> DataType&;
private:
    std::vector<std::list<std::pair<int,DataType>>> m_table;
    auto getHash(const int val) -> std::size_t;
    std::recursive_mutex m_mtx;
    friend std::ostream& operator<< (std::ostream & out , const HashTable<int> & ht);
};
/// @brief insert element (key,value)
/// @tparam DataType 
/// @param key 
/// @param data 
/// @return void
template<typename DataType>
auto HashTable<DataType>::insert(const int key, const DataType & data) -> void
{
    std::lock_guard<std::recursive_mutex> lock(m_mtx);
    auto pos = getHash(key);
    for (auto l : m_table[pos]) {
        if (l.first == key) {
            l.second = data;
            return;
        } 
    }
    m_table[pos].emplace_back(std::make_pair(key, data));
}
/// @brief get value of the 
/// @tparam DataType 
/// @param key 
/// @return DataType& 
template <typename DataType>
auto HashTable<DataType>::get(const int key) -> DataType&
{
    std::lock_guard<std::recursive_mutex> lock(m_mtx);
    int pos = getHash(key);
    auto found = std::find_if(m_table[pos].begin(), m_table[pos].end(), 
        [&key](std::pair<int,DataType> &pair) {
            return key == pair.first;
        });
    if (found != m_table[pos].end()) {
        return found->second;
    } else {
        throw std::invalid_argument("Invalid key!");
    }
}
/// @brief Get hash value (load factor)
/// @tparam DataType 
/// @param key 
/// @return std::size_t
template <typename DataType>
auto HashTable<DataType>::getHash(const int key) -> std::size_t
{
    std::lock_guard<std::recursive_mutex> lock(m_mtx);
    return key % BUCKET_SIZE;
}
/// @brief print hash table constents to console
/// @param out 
/// @param ht 
/// @return std::ostream&
std::ostream& operator << (std::ostream & out, const HashTable<int> & ht) {
    for (auto t : ht.m_table) {
        out << "[ ";
        for (auto l : t) {
            out << "(" << l.first << "," << l.second << ") ";
        }
        out << "]\n";
    }
    return out;
}

#endif //HASHTABLE_HPP_
