/**
 * @file StopState.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef STOPSTATE_HPP_
#define STOPSTATE_HPP_

#include "../IState.hpp"

class StopState : public IState
{
public:
    StopState() = default;
    ~StopState() = default;
    const char* getStateName() override;
    void execute() override;
};

#endif /*STOPSTATE_HPP_*/
