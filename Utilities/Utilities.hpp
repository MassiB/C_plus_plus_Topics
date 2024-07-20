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
#include <type_traits>

namespace
{
/// @brief print_to_console recursive call
/// @return void
auto print_to_console() -> void { std::cout << std::endl; }

/// @brief handle function with no ostream operator
/// @tparam DataType 
/// @tparam T 
template <typename DataType, typename T = void>
struct has_ostream_operator : std::false_type {};

/// @brief Verify if DataType has ostream operator
/// @tparam DataType 
template <typename DataType>
struct has_ostream_operator <DataType, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<DataType>())>> : std::true_type {};

} /// anonymous namespace

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/// @brief print element to console
/// @tparam DataType 
/// @tparam ...Args 
/// @param data 
/// @param ...args 
/// @return void
template <typename DataType, typename... Args>
auto print_to_console(DataType && data, Args &&... args) -> typename
    std::enable_if<has_ostream_operator<DataType>::value, void>::type
{
    std::cout << data << ", ";
    print_to_console(std::forward<Args>(args)...);
}

/// @brief print data of a container
/// @tparam DataType 
/// @param container 
/// @return void
template <template <typename DataType> class Container, typename DataType>
auto print_to_console(const Container<DataType> &container) -> typename
    std::enable_if<has_ostream_operator<DataType>::value, void>::type
{
    std::cout << "[ ";
    for (auto &c : container)
        std::cout << c << " ";
    std::cout << "]\n";
}

/// @brief unused parameter function
/// @tparam ...Args 
/// @param ...arg 
/// @return void
template <typename... Args>
auto unused(Args... arg) -> void { /*unused parameters*/ }

#endif /*UTILITIES_HPP_*/
