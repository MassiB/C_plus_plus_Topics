/**
 * @file Logger.cpp
 * @author Massinissa Bandou
 * @brief 
 * @version 0.1
 * @date 2024-07-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Logger.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>


/// @brief constructor
Logger::Logger() : m_thread(&Logger::write, this)
{}

/// @brief destructor
Logger::~Logger()
{
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        running.store(false);
        m_cv.notify_one();
    }
    if (m_thread.joinable())
        m_thread.join();
    if (m_outfile.is_open())
        m_outfile.close();
}

/// @brief Logger initialization
/// @param log_level 
/// @param filename 
/// @return void
auto Logger::initialize(LEVEL log_level, const std::string & filename) -> void
{
    std::lock_guard<std::mutex> lock(m_instance_mtx);
    if (nullptr == m_instance)
        m_instance.reset(new Logger());
    if (m_outfile.is_open())
        m_outfile.close();
    m_outfile.open(filename);
    m_level = log_level;
}

/// @brief get a single instance of Logger
/// @return std::unique_ptr<Logger>&
auto Logger::getInstance() -> std::unique_ptr<Logger>&
{
    std::lock_guard<std::mutex> lock(m_instance_mtx);
    if (nullptr == m_instance)
        throw std::runtime_error("Logger instance is not initialized!");
    return m_instance;
}

/// @brief write into output file
/// @return void
auto Logger::write() -> void
{
    if (!m_outfile.is_open()) {
        return;
    }
    for (;;)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [this]() -> bool { return !running.load() || !m_message_queue.empty();});
        if (!running.load() && m_message_queue.empty())
            break;
        while (!m_message_queue.empty())
        {
            auto msg = std::move(m_message_queue.front());
            m_message_queue.pop();
            auto time = getCurrentTime();
            m_outfile <<time << ": " << msg << "\n"; 
        }
    }
}

/// @brief current time in a string format
/// @return std::string
auto Logger::getCurrentTime() -> std::string
{
    auto current_time = std::time(nullptr);
    auto local_time = std::localtime(&current_time);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
