#ifndef MUSIC_H
#define MUSIC_H
#include <atomic>
#include <string>
#include <utility>
#include <windows.h>
namespace ducktimer{
    class music{
    public:
        explicit music(std::string fname):filename(std::move(fname)){};
        void run() const;
    private:
        void mointerKeyboard() const;
        void playMusic() const;
    private:
        std::string filename;
        static std::atomic<bool> running;
    };
}
#endif
