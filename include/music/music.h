#ifndef MUSIC_H
#define MUSIC_H
#include <string>

namespace ducktimer{
    class music{
    public:
        music(std::string fname):filename(fname){};
        void play() const;
    private:
        std::string filename;
    };
}
#endif