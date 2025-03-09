#include "utils.h"
#include <iostream>
#include <thread>
#include <cmath>

namespace ducktimer {

    char tools::ibuffer[BUFFER_SIZE] = {0};
    char tools::obuffer[BUFFER_SIZE] = {0};

    void tools::clearCurrentLine(int len) {
        int t = 1000;
        while(len > 0) {
            std::cout << "\b \b";
            std::this_thread::sleep_for(std::chrono::milliseconds(t));
            t = static_cast<int>(pow(t, 0.5));
            len --;
        }
    }

    void tools::setIONewBuffer(){
        setvbuf(stdout, obuffer, _IONBF, sizeof(obuffer));
        setvbuf(stdin, ibuffer, _IONBF, sizeof(ibuffer));
    }

}
