#ifndef TIMER_H
#define TIMER_H
#include <string>
#include "music.h"

namespace ducktimer {
    class timer {
    public:
        explicit timer(int dur, std::string fname):m_duration(dur), m_music(fname){};
        void run() const;
    private:
        void panel() const;
        void setDuration() const;
        void startDuration() const;
        void startTimer() const;

    private:
        int mutable m_duration;
        music m_music;
    };
}
#endif
