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
#include <memory>
#include <thread>
#include <queue>
#include <string>

/// @brief Logger class to log info 
class Logger
{
    auto getCurrentTime() -> std::string;
    auto write() -> void;
    explicit Logger(const std::string & _filename);
public:
    virtual ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger &&) = delete;
    Logger& operator=(Logger&&) = delete;

    static auto initialize(const std::string & filename) -> void;
    static auto getInstance() -> std::unique_ptr<Logger>&;
    auto log(std::string && message) -> void;
private:
    std::atomic<bool> running {true};
    std::string m_filename;
    inline static std::mutex m_instance_mtx;
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::thread m_thread;
    std::queue<std::string> m_message_queue;
    inline static std::unique_ptr<Logger> m_instance {nullptr};
};

#endif /*LOGGER_HPP_*/
