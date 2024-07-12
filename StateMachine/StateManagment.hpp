/**
 * @file StateManagment.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef STATEMANAGMENT_HPP_
#define STATEMANAGMENT_HPP_

#include "IState.hpp"
#include <memory>

/// @brief State management class
class StateManagement
{
public:
    StateManagement() = default;
    virtual ~StateManagement() = default;
    
    auto setState(std::unique_ptr<IState> &newState) -> void;
    auto getState() -> IState&;
    auto getStateName() -> const char*;
    auto run() -> void;
    
private:
    std::unique_ptr<IState> m_current_state {nullptr};
};

#endif /*STATEMANAGMENT_HPP_*/
