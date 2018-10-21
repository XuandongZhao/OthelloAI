#ifndef MAIN_NETWORK_H
#define MAIN_NETWORK_H

#include "board.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>

#ifdef _WINDOWS
#include <windows.h>
#else

#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

class Network {
private:
    const std::string IP = "http://10.180.58.5:5000/";
public:
    std::string board_last(int num);

    std::string create_session(int num);

    Board board_string(int num);

    std::string get_move(int x, int y, int num, std::string color);

    std::string get_trun(int num);

    std::string network(std::string content);
};
#endif //MAIN_NETWORK_H
