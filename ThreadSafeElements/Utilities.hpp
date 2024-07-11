/**
 * @file Utilities.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <iostream>

/// @brief unused parameter function
/// @tparam ...Args 
/// @param ...arg 
/// @return void
template <typename... Args>
auto unused(Args... arg) -> void { /*unused parameters*/ }

/// @brief print_to_console recursive call
/// @return void
auto print_to_console() -> void
{
    std::cout << std::endl;
}

/// @brief print element to console
/// @tparam DataType 
/// @tparam ...Args 
/// @param data 
/// @param ...args 
/// @return void
template <typename DataType, typename... Args>
auto print_to_console(DataType && data, Args &&... args) -> void
{
    std::cout << data << ',';
    print_to_console(std::forward<Args>(args)...);
}

/// @brief print elements of any container
/// @tparam Container 
/// @param begin 
/// @param end 
/// @return void
template <class Container>
auto print_to_console(typename Container::iterator begin, typename Container::iterator end) -> void
{
    std::cout << "[ ";
    for (auto itr = begin; itr != end; ++itr)
        std::cout << *itr << " ",
    std::cout << "]\n"; 
}

#endif /*UTILITIES_HPP_*/
