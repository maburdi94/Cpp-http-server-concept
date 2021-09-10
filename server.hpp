//
// Created by Michael Burdi on 8/29/21.
//

#ifndef C__20_SANDBOX_SERVER_HPP
#define C__20_SANDBOX_SERVER_HPP

#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <thread>

#include <unordered_map>
#include <cstring>
#include <string>

#include "response.hpp"
#include "request.hpp"


// On my Quad-core Macbook Pro with Hyper-Threading this
// returns 8 (4 physical cores + 4 virtual cores)
#define MAX_THREADS std::thread::hardware_concurrency();



class Server {

    void (*handler)( Request&, Response&) = nullptr;

public:

    // Create a thread pool
//    unsigned poolSize = MAX_THREADS;



    void onrequest(void ( Request &request, Response &response ) );
    int listen(unsigned port);
};

#endif //C__20_SANDBOX_SERVER_HPP
