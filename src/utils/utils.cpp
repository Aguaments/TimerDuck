#include "utils.h"
#include <iostream>
#include <thread>
#include <cmath>
#include <mutex>

#define POINT_NUM 3
#define BASE_INTERVAL 1000

namespace ducktimer {

    std::unique_ptr<utils> utils::instance = nullptr;
    std::mutex utils::mtx;
    int utils::m_point_num = POINT_NUM;

    utils& utils::getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if(instance == nullptr) {
            auto new_instance = new utils();
            std::lock_guard<std::mutex> innerlock(mtx);
            if(!instance) {
                instance.reset(new_instance);
            }
        }
        return *instance;
    }


    void utils::clearCurrentLine(int len) {
        int t = BASE_INTERVAL;
        while(len > 0) {
            std::cout << "\b \b";
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            t = static_cast<int>(pow(t, 0.5));
            len --;
        }
    }

    void utils::printPoint() {
        for(int i = 0; i < m_point_num; ++ i) {
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(i == 2 ? 1500 : 1000));
        }
        auto space = std::string(" ", m_point_num);
        auto back = std::string("\b", m_point_num);
        std::cout << back << space <<back; // 褪掉打印出来的“.”
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    void utils::setPointNums(const int &nums) {
        m_point_num = nums;
    }
}
