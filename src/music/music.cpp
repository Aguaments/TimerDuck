#include "music.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


namespace ducktimer{
    void music::playmusic() const{
        std::string command = "open \"" + filename +"\" type mpegvideo alias mp3" ;
        mciSendString(command.c_str(), NULL, 0, NULL);
        // 播放
        mciSendString("play mp3", NULL, 0, NULL);
        
        // 等待用户输入
        system("pause");

        // 关闭 MP3
        mciSendString("close mp3", NULL, 0, NULL);
    }
}