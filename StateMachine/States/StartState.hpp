/**
 * @file StartState.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef STARTSTATE_HPP_
#define STARTSTATE_HPP_

#include "../IState.hpp"

class StartState : public IState
{
public:
    StartState() = default;
    ~StartState() = default;
    const char* getStateName() override;
    void execute() override;
};

#endif /*STARTSTATE_HPP_*/
