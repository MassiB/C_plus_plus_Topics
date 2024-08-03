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

#include "Level.hpp"

#include <atomic>
#include <fstream>
#include <sstream>
#include <condition_variable>
#include <mutex>
#include <memory>
#include <thread>
#include <queue>

/// @brief Logger class to log info 
class Logger
{
    Logger();
    auto getCurrentTime() -> std::string;
    auto write() -> void;
    template <typename DataType, typename ... Args>
    auto logMessage(const DataType &data, const Args &... args) -> std::string;
    template <typename DataType>
    auto logMessage(const DataType & data) -> std::string;
public:
    virtual ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger &&) = delete;
    Logger& operator=(Logger&&) = delete;

    static auto initialize(LEVEL log_level, const std::string & filename) -> void;
    static auto getInstance() -> std::unique_ptr<Logger>&;
    template <typename ... Args>
    auto log(LEVEL level, const Args &... args) -> void;
private:
    inline static std::unique_ptr<Logger> m_instance {nullptr};
    inline static std::ofstream m_outfile;
    inline static LEVEL m_level {LEVEL::LEVEL_DEBUG};
    inline static std::mutex m_instance_mtx;
    std::atomic<bool> running {true};
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::thread m_thread;
    std::queue<std::string> m_message_queue;   
};

/// @brief 
/// @tparam ...Args 
/// @param level 
/// @param ...args 
/// @return void
template <typename ... Args>
auto Logger::log(LEVEL level, const Args&... args) -> void
{
    if (level < m_level)
        return;
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        auto level_str = convert_level_to_string(level);
        auto str = logMessage(level_str, args...);
        m_message_queue.push(str);
    }
    m_cv.notify_one();
}

/// @brief log messages
/// @tparam DataType 
/// @tparam ...Args 
/// @param data 
/// @param ...args 
/// @return std::string
template <typename DataType, typename ... Args>
auto Logger::logMessage(const DataType &data, const Args &... args) -> std::string
{
    std::ostringstream oss;
    oss << data << " ";
    auto str = oss.str();
    str.append(logMessage(args...));
    return str;
}

/// @brief log single data message
/// @tparam DataType 
/// @param data 
/// @return std::string
template <typename DataType>
auto Logger::logMessage(const DataType & data) -> std::string
{
    std::ostringstream oss;
    oss << data;
    return oss.str();
}

/// Defines logging verbosity
#define LOG_DEBUG(...) Logger::getInstance()->log(LEVEL::LEVEL_DEBUG,  __VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance()->log(LEVEL::LEVEL_ERROR, __VA_ARGS__)
#define LOG_INFO(...) Logger::getInstance()->log(LEVEL::LEVEL_INFO, __VA_ARGS__)
#define LOG_WARNING(...) Logger::getInstance()->log(LEVEL::LEVEL_WARNING, __VA_ARGS__)
#define LOG_CRITICAL(...) Logger::getInstance()->log(LEVEL::LEVEL_CRITICAL, __VA_ARGS__)

#endif /*LOGGER_HPP_*/
