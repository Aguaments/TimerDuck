#include "utils.h"
#include <iostream>
#include <thread>
#include <cmath>
#include <mutex>
#include <iomanip>

#define POINT_NUM 3
#define BASE_INTERVAL 1000

namespace ducktimer {

    std::unique_ptr<utils> utils::instance = nullptr;
    std::recursive_mutex utils::mtx;

    // Get singlton
    utils& utils::getInstance() {
        std::lock_guard<std::recursive_mutex> lock(mtx);
        if(instance == nullptr) {
            auto new_instance = new utils();
            std::lock_guard<std::recursive_mutex> innerlock(mtx);
            if(!instance) {
                instance.reset(new_instance);
            }
        }
        return *instance;
    }

    // Clear current line
    void utils::clearCurrentLine(int len) {
        int t = BASE_INTERVAL;
        while(len > 0) {
            std::cout << "\b \b";
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            t = static_cast<int>(pow(t, 0.5));
            len --;
        }
    }

    // Point print module
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

    // Choose Yes or No
    int utils::isYOrN(){
        int ret = 0;
        char ans = 'Y'; // Default setting
        std::cout << "Choose Y or N(Yes/No, Default Y) " ;
        if((std::cin >> ans).good()){
            if(ans == 'N' || ans == 'n') {
                std::cout << "Set success." << std::endl;
                ret = 1;
            }
            else if(ans == 'Y' || ans == 'y'){
                std::cout << "Set fail, you choose no.";
            }
            else{
                std::cout << "/(= _ =)\\ DAMN!" << std::endl;
            }
        }
        else{
            auto curr_time = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(curr_time);
            std::tm * local_time = std::localtime(&now_time);
            std::cerr << "[" << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << "] Input content error." << std::endl;
        }
        return ret;
    }
}
