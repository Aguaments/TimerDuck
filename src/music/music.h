#ifndef MUSIC_H
#define MUSIC_H
#include <string>
#include <windows.h>
namespace ducktimer{
    class music{
    public:
        explicit music(std::string fname):filename(fname){};
        void playmusic() const;
    private:
        std::string filename;
    };
}
#endif