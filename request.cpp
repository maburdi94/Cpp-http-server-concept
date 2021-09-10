//
// Created by Michael Burdi on 9/6/21.
//


#include "request.hpp"

std::unordered_map<std::string, std::string> parse_headers(const std::string& data) {
    std::unordered_map<std::string, std::string> headers = {};
    std::istringstream f(data);
    std::string line;

    while (std::getline(f, line)) {
        size_t n = line.find_first_of(':');
        headers.insert({line.substr(0,n), line.substr(n + 1)});
    }
    return headers;
}


Request::Request(int socket) : socket(socket) {

    std::string data;
    char buff[1024];

    while (recv(socket , buff , 1024 , 0 ) > 0) {
        data.append(buff);

        // Wait until find end of HTTP headers
        if (size_t n = data.find("\r\n\r\n")) {

            auto first_line_end = data.find_first_of("\r\n");
            std::stringstream ss(data.substr(0,first_line_end));

            ss >> this->method;
            ss >> this->url;
            ss >> this->version;

            this->headers = parse_headers(data.substr(first_line_end + 2, n - first_line_end));

            data = data.substr(n + 4);

            break;
        }

        // Clear the buffer so we don't get junk bytes
        memset(buff, 0, 1024);
    }

    // If Content-Length is present, we expect a body
    if (this->headers.contains("Content-Length")) {
        // Read Content-Length
        int length = std::stoi(this->headers.at("Content-Length"));

        // Start reading in body content starting with bytes already read
        size_t received = data.length();

        // Read until end of content
        while (received != length && (received += recv(socket , buff , 1024 , 0 )) > 0) {
            data.append(buff);

            // Clear the buffer so we don't get junk bytes
            memset(buff, 0, 1024);
        }

        this->body = data;
    }
}

std::ostream& operator<<(std::ostream &out, const Request &req) {
    out << "METHOD: " << req.method << '\n';
    out << "URL: " << req.url << '\n';
    out << "VERSION: " << req.version << '\n';
    out << "HEADERS: " << '\n';
    for (auto [key, value] : req.headers)
        out << key << ": " << value << '\n';
    out << "BODY: " << '\n';
    out << req.body << '\n';
}

