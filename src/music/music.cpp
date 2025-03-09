#include "music.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


namespace ducktimer{
    void music::playmusic() const{
        char fullPath[MAX_PATH];
        GetFullPathName("test.mp3", MAX_PATH, fullPath, NULL);

        std::string command = "open \"" + std::string(fullPath) + "\" type mpegvideo alias mp3";
        MCIERROR err = mciSendString(command.c_str(), NULL, 0, NULL);
        
        if (err != 0) {
            std::cerr << "Failed to open MP3, error code: " << err << std::endl;
            exit(1);
        }

        mciSendString("play mp3", NULL, 0, NULL);
        std::cout << "Playing MP3..." << std::endl;
        system("pause");

        mciSendString("close mp3", NULL, 0, NULL);
    }
}
