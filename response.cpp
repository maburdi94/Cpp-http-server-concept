//
// Created by Michael Burdi on 9/6/21.
//

#include "response.hpp"

Response::Response(int socket) : socket(socket) {}

void Response::end(const std::string &data = "") {

    this->body += data;

    std::ostringstream oss;
    oss << this->version << this->statusCode << this->statusText << std::endl;

    this->headers.insert({"Content-Length", std::to_string(data.length())});

    for (auto &&[key, value] : headers)
        oss << key << ':' << value << std::endl;

    oss << std::endl;
    oss << this->body;

    std::string &&s = oss.str();

    write(this->socket, s.data(), s.size());
}


void Response::setHeader(std::string&& name, std::string&& value) {
    this->headers.insert_or_assign(name, value);
}