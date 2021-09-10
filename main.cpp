#include <iostream>

#include "server.hpp"


using std::cout;
using std::endl;
using std::string;


int main() {

    Server s;
    s.onrequest([](Request& req, Response &res) {
        cout << req.method << " " << req.url << endl;

        if (req.url == "/") {
            string body = R"(
            <h1>This is a demo server written in C++!</h1>
            <a href="/hello"><button>Say Hello</button></a>
            )";

            res.setHeader("Content-Type", "text/html");
            res.end(body);
        }
        else if (req.url == "/hello") {
            string body = "<h1>Hello!</h1>";

            res.setHeader("Content-Type", "text/html");
            res.end(body);
        }
        else {
            string body = "<h1>404 Not Found</h1>";

            res.setHeader("Content-Type", "text/html");
            res.end(body);
        }

    });
    s.listen(80);

    return 0;
}
