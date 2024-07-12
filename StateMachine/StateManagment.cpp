/**
 * @file StateManagment.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "StateManagment.hpp"

/// @brief set current state to new state
/// @param newState 
/// @return void
auto StateManagement::setState(std::unique_ptr<IState> &newState) -> void
{
    m_current_state.reset(nullptr);
    m_current_state = std::move(newState);
}

/// @brief get current state 
/// @return IState
auto StateManagement::getState() -> IState&
{
    return *(m_current_state.get());
}

/// @brief return current state typeid
/// @return const char*
auto StateManagement::getStateName() -> const char*
{
    if (nullptr != m_current_state)
        m_current_state->getStateName();
    return {};
}

/// @brief execute state
/// @return void
auto StateManagement::run() -> void
{
    if (nullptr != m_current_state)
        m_current_state->execute();
}
