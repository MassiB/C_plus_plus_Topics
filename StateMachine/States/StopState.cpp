/**
 * @file StopState.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "StopState.hpp"

#include <iostream>
#include <typeinfo>

const char* StopState::getStateName()
{
    return typeid(this).name();
} 

void StopState::execute()
{
    /* To be implemented by the user */
    std::cout << typeid(this).name() << ":" << __FUNCTION__ << std::endl;
}
