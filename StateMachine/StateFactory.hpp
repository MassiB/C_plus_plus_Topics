/**
 * @file StateFactory.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef STATEFACTORY_HPP_
#define STATEFACTORY_HPP_

#include "IState.hpp"
#include "States/StateEnum.hpp"

#include <memory>

/// @brief StateFactory class
class StateFactory
{
public:
    StateFactory() = default;
    virtual ~StateFactory() = default;
    static std::unique_ptr<IState> createState(STATE_ENUM enumType);
};

#endif /*STATEFACTORY_HPP_*/
