/**
 * @file StartState.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "StartState.hpp"

#include <iostream>
#include <typeinfo>

const char* StartState::getStateName()
{
    return typeid(this).name();
} 

void StartState::execute()
{
    /* To be implemented by the user */
    std::cout << typeid(this).name() << ":" << __FUNCTION__ << std::endl;
}
