//
// Created by 赵宣栋 on 2018/6/6.
//

#ifndef ALPHA_REVERSI_NETWORK_H
#define ALPHA_REVERSI_NETWORK_H

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPSTR "47.89.179.202"
#define PORT 5000
#define BUFSIZE 1024

std::string create_session(int num);
std::string board_string(int num);
std::string get_move(int x, int y, int num, std::string color);
std::string get_trun(int num);
std::string network(std::string content);

#endif //ALPHA_REVERSI_NETWORK_H
