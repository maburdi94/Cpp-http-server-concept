//
// Created by Michael Burdi on 9/6/21.
//

#ifndef C__20_SANDBOX_REQUEST_HPP
#define C__20_SANDBOX_REQUEST_HPP

#include <unistd.h>
#include <sys/socket.h>

#include <cstring>

#include <sstream>
#include <unordered_map>
#include <string>

struct Request {
    int socket;

public:
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    std::string method;
    std::string url;
    std::string version;

    explicit Request(int);
    friend std::ostream& operator<<(std::ostream &, const Request &);

};



#endif //C__20_SANDBOX_REQUEST_HPP
