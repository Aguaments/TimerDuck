#ifndef TIMER_H
#define TIMER_H
#include <string>

namespace ducktimer {
    class timer {
    public:
        explicit timer(int dur):duration(dur), filepath("./bgm.mp3"){};
        void run() const;
    private:
        void panel() const;
        void setDuration() const;
        void startDuration() const;
        void startTimer() const;
        int mutable duration;
        std::string filepath;
    };
}
