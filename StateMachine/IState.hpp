/**
 * @file IState.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef ISTATE_HPP_
#define ISTATE_HPP_

/// @brief state interface
class IState
{
public:
    IState() = default;
    virtual ~IState() = default;
    virtual const char* getStateName() = 0;
    virtual void execute() = 0;
};

#endif /*ISTATE_HPP_*/
