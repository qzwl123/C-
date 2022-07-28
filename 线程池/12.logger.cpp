/*************************************************************************
	> File Name: 12.logger.cpp
	> Author: 秃头王
	> Mail: 1658339000@qq.com
	> Created Time: 2022年07月27日 星期三 15时38分31秒
 ************************************************************************/

/*
 *  cout << "hellow world" << 123 << endl;
 *  当多个线程都在操作时候有的在打印hello world有的在打印123
 *  如果把这这个语句变成原子操作
 *  原子操作：不可分割的一个单独的操作
 *  原子操作必加锁、原子操作你不加锁在作死
 *  
 *  cout << "hellow world" << 123 << endl; -> 对应了一个单独的缓冲区
 *  cout << "hellow world" << 123 << endl; -> 对应了一个单独的缓冲区
 *  cout << "hellow world" << 123 << endl; -> 对应了一个单独的缓冲区 -> 对象
 *  在现在这个场景种 cout 对应的都是一个所以不安全
 *
 *  用到临时对象
 */

/*
    std::ostringstream s;
    s << "hellow world" << " " << 123 << std::endl;
    std::cout << s.str();
*/

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <mutex>
#include "threadpoolPlus.h"

/*
#define LEVEL(str) ttw::LogLevel::##str
#define LEVEL_INFO    LEVEL(INFO)
#define LEVEL_WARNING LEVEL(WARNING)
#define LEVEL_DEBUG   LEVEL(DEBUG)
#define LEVEL_ERROR   LEVEL(ERROR)
#define LEVEL_FATAL   LEVEL(FATAL)
*/

// __FILE__(文件名) __LINE__(行哈) level(日志等级)
#define LOG(level) ttw::Logger::LoggerStream(level, __FILE__, __LINE__, ttw::ttw_log)
#define LOG_INFO LOG(ttw::LogLevel::INFO)
#define LOG_WARNING LOG(ttw::LogLevel::WARNING)
#define LOG_DEBUG LOG(ttw::LogLevel::DEBUG)
#define LOG_ERROE LOG(ttw::LogLevel::ERROR)
#define LOG_FATAL LOG(ttw::LogLevel::FATAL)
#define SET_LEVEL(level) ttw::ttw_log.set_level(level)

namespace ttw {
    // 枚举类
    class LogLevel {
    public :
        static const int INFO ;
        static const int WARNING;
        static const int DEBUG;
        static const int ERROR;
        static const int FATAL;
    };
    const int LogLevel::INFO = 1;
    const int LogLevel::WARNING = 2;
    const int LogLevel::DEBUG = 3;
    const int LogLevel::ERROR = 4;
    const int LogLevel::FATAL = 5;
    std::map<int, std::string> LevelString = {
        {LogLevel::INFO, "INFO"},
        {LogLevel::WARNING, "WARNING"},
        {LogLevel::DEBUG, "DEBUG"},
        {LogLevel::ERROR, "ERROR"},
        {LogLevel::FATAL, "FATAL"}
    };

    class Logger {
    public :
        Logger() : LOG_LEVEL(LogLevel::INFO) {}
        // 临时对象
        class LoggerStream : public std::ostringstream {
        public :
            LoggerStream(int level, const char *file_name, int line_no, Logger &raw_log) : line_no(line_no),level(level), raw_log(raw_log) {
                std::ostringstream &now = *this;
                now << "[" << file_name << " : " << LevelString[level] << "]"; 
            }
            ~LoggerStream() {
                if(level < raw_log.LOG_LEVEL) return ;
                // 互斥锁
                std::unique_lock<std::mutex> lock(raw_log.m_mutex);
                std::cout << this->str() << "(" << line_no << ")" << std::endl;
            }
        private :
            // 行号、日志等级
            int line_no, level;
            Logger &raw_log;
        };
        void set_level(int level) { this->LOG_LEVEL = level; }
        int LOG_LEVEL;
        std::mutex m_mutex;
    };
    // 输出流对象
    Logger ttw_log;

} // end of ttw


void func(int a, int b, int c) {
    //cout << this_thread::get_id() << "begin" << endl;
    LOG_INFO << a << " " << b << c;
    return ;
}


int main() {
    // SET_LEVEL(ttw::LogLevel::DEBUG);
    LOG_INFO << "hellow world" << " " << 123 ;
    LOG_WARNING << "hellow world" << " " << 123;
    LOG_DEBUG << "hellow world" << " " << 123;
    LOG_ERROE << "hellow world" << " " << 123;
    LOG_FATAL << "hellow world" << " " << 123;
    
    ttw::ThreadPool tp;
    for(int i = 0; i < 100; i++) {
        tp.add_task(func, i, 2 * i, 3 * i);

    }
    tp.stop();
   
    return 0;
}
