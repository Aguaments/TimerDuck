#include "music.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <thread>
#include <conio.h>
#include "utils.h"
#pragma comment(lib, "winmm.lib")

#define KEYBOARD_CATCH_INTERVAL


namespace ducktimer{

    std::atomic<bool> music::running = false;

    void music::mointerKeyboard() const {
        while(running) {
            if(_kbhit()) {
                _getch();
                running = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(KEYBOARD_CATCH_INTERVAL));
    }

    void music::playMusic() const{
        char fullPath[MAX_PATH];
        GetFullPathName(filename.c_str(), MAX_PATH, fullPath, NULL);

        std::string command = "open \"" + std::string(fullPath) + "\" type mpegvideo alias mp3";
        MCIERROR err = mciSendString(command.c_str(), NULL, 0, NULL);

        if (err != 0) {
            std::cerr << "Failed to open MP3, error code: " << err << std::endl;
            exit(1);
        }

        mciSendString("play mp3", NULL, 0, NULL);
        std::cout << "Playing this music (Input any key to close the music) -- [ Music: " << filename  << " ] " ;
        while(running) {
            utils::printPoint();
        }
        mciSendString("close mp3", NULL, 0, NULL);
    }

    void music::run() const{
        std::thread t1(playMusic);
        std::thread t2(mointerKeyboard);

        t1.join();
        t2.join();
        std::cout << std::endl;
        std::cout <<"stop" <<std::endl;
        std::cin.get();
    }
}
