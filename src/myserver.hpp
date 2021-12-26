#ifndef MYSERVER_HPP
#define MYSERVER_HPP

#include <netinet/in.h>


class myserver {
    int socket_fd;
    int opt;
    sockaddr_in address;
    bool is_online;

public:
    void open_connection(int port, int max_connection);
    void close_connection();

    int get();
    bool online();

    int get_socket_fd();
};

#endif
