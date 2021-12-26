#include <csignal>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "myserver.hpp"


void myserver::open_connection(int port, int max_connection) {
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        raise(EXIT_FAILURE);
    }

    opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        raise(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socket_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        raise(EXIT_FAILURE);
    }

    if (listen(socket_fd, max_connection) < 0) {
        perror("listen failed");
        raise(EXIT_FAILURE);
    }

    is_online = true;
}


void myserver::close_connection() {
    is_online = false;
    close(socket_fd);
}


int myserver::get() {
    int addrlen = sizeof(address);
    int new_socket = accept(socket_fd, (sockaddr*)&address, (socklen_t*)&addrlen);

    if (new_socket < 0) {
        perror("accept failed");
        raise(EXIT_FAILURE);
    }

    return new_socket;
}


bool myserver::online() {
    return is_online;
}


int myserver::get_socket_fd() {
    return socket_fd;
}
