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
#include <functional>
#include <type_traits>
#include <utility>

namespace algo
{
    namespace
    {
        /// @brief predicate
        /// @tparam DataType 
        template <typename DataType>
        using Predicate = std::function<void(DataType&)>;

        /// @brief handle DataType with no + operator
        /// @tparam DataType 
        /// @tparam  
        template <typename DataType, typename = void>
        struct has_plus_operator : std::false_type {};
        /// @brief Handle Datatype with + operator
        /// @tparam DataType 
        template <typename DataType>
        struct has_plus_operator<DataType, std::void_t<decltype(std::declval<DataType&> + std::declval<DataType&>)>> : std::true_type {};

        /// @brief recursive call
        /// @tparam DataType 
        /// @param data 
        /// @return DataType
        template <typename DataType>
        auto sum(DataType && data) -> DataType
        {
            return std::forward<DataType>(data);
        }
    }; /// anonymous namespace
    
/// @brief sum all parameters
/// @tparam DataType 
/// @tparam ...Args 
/// @param data 
/// @param ...args 
/// @return std::common_type_t<DataType, Args...>
template<typename DataType, typename ...Args>
auto sum(DataType && data, Args &&...args) -> std::common_type_t<DataType, Args...>
{
    return std::forward<DataType>(data) + sum(std::forward<Args>(args)...);
}

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

/// @brief parallel for_each algorithm
/// @tparam DataType 
/// @param container 
/// @param pred 
/// @return void
template <template <typename> class Container, typename DataType>
auto parallel_for_each(Container<DataType> &container, Predicate<DataType> pred) -> void
{
    static int num_hw_cores = std::thread::hardware_concurrency();
    const int container_size = container.size();
    if (container_size == 0) return;
    int max_num_threads = (container_size % num_hw_cores == 0) ? container_size / num_hw_cores :
        (container_size / num_hw_cores) + 1;
    max_num_threads = std::min(max_num_threads, num_hw_cores);
    int elements = container_size / max_num_threads;
    for (unsigned int i(0); i < max_num_threads; ++i) {
        std::thread([&]() {
            int start = i * elements;
            int end = start + elements;
            if (end > container_size) end = container_size;
            for (unsigned int j(start); j < end; ++j)
                pred(container[j]);
        }).join();
    }
}


} /// namespace algo

#endif ///ALGORITHMS_HPP_
