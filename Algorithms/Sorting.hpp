/**
 * @file Sorting.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SORTING_HPP_
#define SORRING_HPP_

#include <algorithm>
#include <execution>
#include <functional>
#include <future>

namespace sort
{
    namespace 
    {
    typedef unsigned long long uLL;
    /// @brief Comparator definition
    /// @tparam DataType 
    template <typename DataType>
    using Comparator = std::function<bool(DataType&,DataType&)>;
    } /// anonymous namespace

    /// @brief Ascending order
    /// @tparam DataType 
    template <typename DataType>
    Comparator<DataType> ascending = [](DataType &_in1, DataType &_in2) -> bool { return _in1 > _in2; };
    
    /// @brief Descending order
    /// @tparam DataType 
    template <typename DataType>
    Comparator<DataType> descending = [](DataType &_in1, DataType &_in2) -> bool { return _in1 < _in2; };

/// @brief selection sort algorithm
/// @tparam DataType 
/// @param begin 
/// @param end 
/// @param predicate 
/// @return void
template <template <typename> class Container, typename DataType>
auto selection_sort(typename Container<DataType>::iterator begin, typename Container<DataType>:: iterator end,
                        Comparator<DataType> predicate = ascending<DataType>) -> void
{
    for (auto itr1 = begin; itr1 != end; ++itr1) {
        for (auto itr2 = itr1; itr2 != end; ++itr2){
            if (predicate(*itr1, *itr2))
                std::swap(*itr1, *itr2);
        }
    }
}

/// @brief bubble sort algorithm
/// @tparam DataType 
/// @param container 
/// @param predicate 
/// @return void
template <template <typename> class Container, typename DataType>
auto bubble_sort(Container<DataType> &container, Comparator<DataType> predicate = ascending<DataType>) -> void
{
    for (uLL i(0); i < container.size(); ++i) {
        bool stop = true;
        for (uLL j(0); j < container.size() - 1; ++j) {
            if (predicate(container[j], container[j+1])) {
                std::swap(container[j], container[j+1]);
                stop = false;
            }
        }
        if (stop) break;
    }
}

/// @brief parallel quick sort algorithm
/// @tparam DataType 
/// @param container 
/// @param predicate 
/// @return void
template <template <typename> class Container, typename DataType>
auto parallel_quick_sort(Container<DataType> &container, Comparator<DataType> predicate = ascending<DataType>) -> void
{
    std::size_t size = container.size();
    if (size <= 1) return;
    Container<DataType> right_container, left_container;
    std::size_t pivot_index = size/2;
    DataType pivot_value = container[pivot_index];
    for (uLL i(0); i < size; ++i) {
        if (i == pivot_index) continue;
        if (predicate(container[i], container[pivot_index]))
            right_container.push_back(container[i]);
        else
            left_container.insert(left_container.begin(), container[i]);
    }
    auto fut_right = std::async(std::launch::async, &parallel_quick_sort<Container, DataType>, std::ref(right_container), predicate);
    auto fut_left = std::async(std::launch::async, &parallel_quick_sort<Container, DataType>, std::ref(left_container), predicate);
    /*wait the task to be completed*/
    fut_right.get();
    fut_left.get();
    container.clear();
    container.insert(container.end(), left_container.begin(), left_container.end());
    container.push_back(pivot_value);
    container.insert(container.end(), right_container.begin(), right_container.end());
}

} /// namespace sort
#endif /*SORTING_HPP_*/
