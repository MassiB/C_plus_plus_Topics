/**
 * @file Logger.hpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

/// @brief Logger class to log info 
class Logger
{
    auto getCurrentTime() -> std::string;
    auto write() -> void;
public:
    explicit Logger(const std::string & filename);
    virtual ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    auto log(std::string && message) -> void;
private:
    std::atomic<bool> running {true};
    std::string m_filename;
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::thread m_thread;
    std::queue<std::string> m_message_queue;
};

#endif /*LOGGER_HPP_*/
