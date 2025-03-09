#ifndef TIMER_H
#define TIMER_H
#include <string>
#include "music.h"

namespace ducktimer {
    class timer {
    public:
        explicit timer(int dur, std::string fname):duration(dur), m(fname){};
        void run() const;
    private:
        void panel() const;
        void setDuration() const;
        void startDuration() const;
        void startTimer() const;
        int mutable duration;
        music m;
    };
}
#endif
