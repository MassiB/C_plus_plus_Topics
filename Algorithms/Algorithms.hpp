/**
 * @file Algorithms.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef ALGORITHMS_HPP_
#define ALGORITHMS_HPP_

#include <algorithm>
#include <numeric>
#include <iterator>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <future>

namespace algo
{
/// @brief return summ of all elements of a container
/// @tparam DataType 
/// @param begin 
/// @param end 
/// @param start 
/// @return DataType
template <template <typename, typename...> class Container, typename DataType>
auto parallel_sum(const typename Container<DataType>::iterator begin, 
                    const typename Container<DataType>::iterator end,
                        const int start) -> DataType
{
    static constexpr int MAX_NUM = 200;
    const int size = std::distance(begin, end);
    if (size <= MAX_NUM) {
        return std::accumulate(begin, end, start);
    }
    auto mid_point = begin;
    std::advance(mid_point, size / 2);
    auto fut = std::async(std::launch::deferred, &parallel_sum<Container, DataType>, mid_point, end, start);
    return fut.get() +
        parallel_sum<Container, DataType>(begin, mid_point, start);
}

/// @brief find element within the container
/// @tparam DataType 
/// @param begin 
/// @param end 
/// @param data 
/// @return Container<DataType>::iterator
template <template <typename, typename...> class Container, typename DataType>
auto parallel_find(const typename Container<DataType>::iterator begin, 
                    const typename Container<DataType>::iterator end,
                        const DataType &data) -> typename Container<DataType>::iterator
{
    static const int MAX_NUM = 200;
    const int size = std::distance(begin, end);
    if (size <= 200) {
        return std::find(begin, end, data);
    }
    auto mid_point = begin;
    std::advance(mid_point, size / 2);
    auto fut = std::async(std::launch::deferred, parallel_find<Container, DataType>, mid_point, end, data);
    auto result = fut.get();
    return (result != end) ? result : parallel_find<Container, DataType>(begin, mid_point, data);
}

} /// namespace algo

#endif ///ALGORITHMS_HPP_
