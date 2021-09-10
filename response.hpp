//
// Created by Michael Burdi on 9/6/21.
//

#ifndef C__20_SANDBOX_RESPONSE_HPP
#define C__20_SANDBOX_RESPONSE_HPP


#include <unistd.h>

#include <unordered_map>
#include <string>
#include <sstream>

struct Response {
    int socket;

    std::unordered_map<std::string, std::string> headers{
        {"Content-Type", "text/plain"}
    };
    std::string body;
    std::string statusText = "OK";
    std::string statusCode = "200";
    std::string version = "HTTP/1.1";

public:
    explicit Response(int);

    void end(const std::string&);
    void setHeader(std::string&& name, std::string&& value);
};

#endif //C__20_SANDBOX_RESPONSE_HPP
