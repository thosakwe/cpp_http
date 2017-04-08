//
// Created by Tobe on 4/7/17.
//

#ifndef TODO_APP_SERVE_MAIN_H
#define TODO_APP_SERVE_MAIN_H

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netdb.h>
#include <sstream>
#include <thread>
#include <vector>

int serveMain(int concurrency, int port);

#endif //TODO_APP_SERVE_MAIN_H
