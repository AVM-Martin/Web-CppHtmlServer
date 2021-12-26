#include <csignal>
#include <cstdio>
#include <string>

#include <unistd.h>

#include "myconstants.hpp"
#include "mydata.hpp"
#include "myparser.hpp"
#include "myserver.hpp"
#include "mythread.hpp"


myserver server;
mythread workers;


void signal_callback_handler(int signum) {
    // workers.destroy();
    server.close_connection();

    perror("Server stopped");
}


int main(int argc, char const *argv[]) {
    signal(SIGINT, signal_callback_handler);

    server.open_connection(myconstants::PORT, myconstants::MAX_CONNECTION);
    workers.init(myconstants::N_WORKERS);

    while (server.online()) {
        request_data new_data;
        new_data.socket_id = server.get();

        // myparser::parse_request(myconstants::ROOT, new_data);
        // myparser::send_data(new_data);
        // close(new_data.socket_id);

        workers.queue_request(new_data);
    }

    return 0;
}
