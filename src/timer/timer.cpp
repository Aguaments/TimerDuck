#include "timer.h"
#include <iostream>
#include <thread>
#include <iomanip>
#include "utils.h"
#include "msgconstant.h"


namespace ducktimer {
    void timer::run() const {
        panel();
        startTimer();
    }
    void timer::panel() const{
        std::cout << "==========================================================================================" << std::endl;
        std::cout << "      Welcome to use the timer! Let us to start a regular life. (Default 30 minutes)      " << std::endl;
        std::cout << "==========================================================================================" << std::endl;
        std::cout << "                                                                                          " << std::endl;
        std::cout << "                                     \\(^ ~ ^)/                                           " << std::endl;
        std::cout << "                                                                                          " << std::endl;
        std::cout << "==========================================================================================" << std::endl;
    }

    void timer::setDuration() const {
        start: do {
            std::cout << MSG_SET_DURATION;
            if((std::cin >> m_duration).good()){ // 输入没问题
                // 检测输入的duration是否合规，精度为minutes
                if(m_duration < 1) {
                    std::cout << MSG_SET_DURATION_LESS_THAN_1;
                    utils::getInstance().clearCurrentLine(strlen(MSG_SET_DURATION_LESS_THAN_1));
                }
                else{
                    if(m_duration == 30) {
                        std::cout << MSG_SET_DURATION_EQUAL_TO_30 << std::endl;
                        // strlen返回字符串长度，不包含'\0'，清空命令行时长度不需要+1 
                        utils::getInstance().clearCurrentLine(strlen(MSG_SET_DURATION_EQUAL_TO_30)); 
                        // 只要是选择Y/N的都走这个函数
                        if(!utils::getInstance().isYOrN()) continue;
                    }
                    std::cout << MSG_SET_SUCCESS << std::endl;
                    break; // 跳出大循环
                }
            }
            else{ // 输入出现问题
                // 后期构建日志模块重写
                std::cin.clear();
                // 忽略输入流中的剩余部分，直到遇到换行符
                std::cin.ignore();
                auto curr_time = std::chrono::system_clock::now();
                std::time_t now_time = std::chrono::system_clock::to_time_t(curr_time);
                std::tm * local_time = std::localtime(&now_time);
                std::cerr << "[" << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << "] Input content error." << std::endl;
            }
        }while(true);
    }

    void timer::startDuration() const{
        int t = 0;
        std::cout << "Timer started ... (Target: " << m_duration << " minutes)" << std::endl;
        do {
            std::this_thread::sleep_for(std::chrono::minutes(1));
            std::cout << "[Min: " << t + 1 << "] "<< t + 1 << " minute elapsed ... ";
            std::cout << "(Set time duration: " << m_duration ;
            std::cout << " || Total elapsed time : " << t + 1 << ")" << std::endl;
            t ++;
        }while(t < m_duration);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    void timer::startTimer() const {
        do {
            setDuration();
            startDuration();
            m_music.run();
            std::cout << "Continue? " ;
            if(utils::getInstance().isYOrN()) continue;
            else{
                std::cout << MSG_SAY_GOODBYE << std::endl;
                utils::getInstance().clearCurrentLine(strlen(MSG_SAY_GOODBYE));
                break;
            }
        }while(true);
    }
}
