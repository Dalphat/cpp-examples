#ifndef LOG_HPP
#define LOG_HPP

#include <mutex>
#include <functional>
#include <sstream>

#include "share.hpp"

namespace my {
    //Simple logging class: 
    //Provides simple logging interfaces for a logging function
    class Output {
    private:
        std::mutex ss_mutex;
        std::stringstream ss;
        //Logging only functional if a log function is provided
        Share<std::function<void(const std::string&)>> output;
        void logAct(const std::string& s) {
            if (output.get())
                output.get()(s);
        }
    public:
        Output() : output{ NULL } {}

        //Logging support for single argument, example: log(a)
        template <class T>
        void log(T arg) {
            ss_mutex.lock();
            ss.str("");
            ss << arg;
            logAct(ss.str());
            ss_mutex.unlock();
        }
        //Logging support for multiple arguments, example: log(a, b, c)
        template <class T, class... Args>
        void log(T arg, Args... args) {
            log(arg);
            log(args...);
        }
        //Logging support for an linitialzer list of arguments, example: log({ a, b, c })
        template <class T>
        void log(std::initializer_list<T> list) {
            ss_mutex.lock();
            ss.str("");
            for (auto arg : list) {
                ss << arg;
            }
            logAct(ss.str());
            ss_mutex.unlock();
        }
        void setLog(const std::function<void(const std::string&)>& output) {
            this->output = output;
        }
    };
}
#endif // !LOG_HPP
