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
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/// @brief constructor
Logger::Logger(const std::string & filename) : m_filename(std::move(filename)),
    m_thread(&Logger::write, this)
{
}
/// @brief destructor
Logger::~Logger()
{
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        running.store(false);
        m_cv.notify_all();
    }
    if (m_thread.joinable())
        m_thread.join();
}

/// @brief write into output file
/// @return void
auto Logger::write() -> void
{
    static std::ofstream m_outfile(m_filename);
    if (!m_outfile.is_open()){
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
            auto &time = getCurrentTime();
            m_outfile << time << ": " << msg << "\n"; 
        }
    }
    m_outfile.close();
}

/// @brief function interface to log messages
/// @param message 
/// @return void
auto Logger::log(std::string && message) -> void
{
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_message_queue.push(std::move(message));
    }
    m_cv.notify_one();
}

/// @brief 
/// @return current in a string format
auto Logger::getCurrentTime() -> std::string
{
    auto current_time = std::time(nullptr);
    auto local_time = std::localtime(&current_time);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
