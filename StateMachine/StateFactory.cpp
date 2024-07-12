/**
 * @file StateFactory.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "StateFactory.hpp"
#include "States/StartState.hpp"
#include "States/StopState.hpp"
#include "../Utilities/Utilities.hpp"

/// @brief factory IState creation
/// @param enumType 
/// @return std::unique_ptr<IState>
std::unique_ptr<IState> StateFactory::createState(STATE_ENUM enumType)
{
    switch (enumType)
    {
        case STATE_ENUM::STATE_STOP:
            return std::make_unique<StopState>();
        case STATE_ENUM::STATE_START:
            return std::make_unique<StartState>();
        default:
            print_to_console("Unknown enum type");
        return nullptr;
    };
}
