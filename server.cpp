//
// Created by Michael Burdi on 8/29/21.
//


#include "server.hpp"




/**
 * Listen for client connections and spawn a new thread for each connection.
 * @param port
 * @return
 */
int Server::listen(unsigned const port) {

    int sock;
    struct sockaddr_in address{};
    int opt = 1;

    // Creating socket file descriptor
    sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == -1)
    {
        perror("socket failed");
        return EXIT_FAILURE;
    }

    // Forcefully attaching socket to the port 8080
    if (::setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt) ))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );

    socklen_t socklen = sizeof address;

    if (::bind(sock, (struct sockaddr*) &address, sizeof(address)) == -1) {
        perror("Bind error");
        close(sock);
        return EXIT_FAILURE;
    }

    if (::listen(sock, 1)) {
        perror("Listen error");
        close(sock);
        return EXIT_FAILURE;
    }

    printf("Server started %shttp://127.0.0.1:%d%s\n", "\033[92m",port,"\033[0m");

    for (int i = 0; ; i++) {
        int client_sock = ::accept(sock, (struct sockaddr *) &address, &socklen);

        if (client_sock == -1) {
            perror("Accept error");
            close(sock);
            return EXIT_FAILURE;
        }

//        printf("Client with IP %s connected\n", inet_ntoa(address.sin_addr));


        // Joining thread
        std::jthread th([this](int &&socket){
            Request req(socket);
            Response resp(socket);

            this->handler(req, resp);

            close(socket);
        }, client_sock);


    }

}

void Server::onrequest(void pFunction( Request&, Response& )) {
    this->handler = pFunction;
}
