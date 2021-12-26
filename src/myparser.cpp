#include <cstring>
#include <string>

#include <netinet/in.h>

#include "mydata.hpp"
#include "myparser.hpp"


std::string get_file_contents(const std::string& filename) {
    std::FILE *in = std::fopen(filename.c_str(), "rb");

    if (in) {
        std::string contents;

        std::fseek(in, 0, SEEK_END);
        contents.resize(std::ftell(in));

        std::rewind(in);
        std::fread(&contents[0], 1, contents.size(), in);
        std::fclose(in);

        return contents;
    }

    throw (errno);
}


void myparser::parse_request(const std::string& root, request_data& data) {
    const int len = 64;

    char buffer[len];
    recv(data.socket_id, buffer, len, 0);

    char uri[len];
    sscanf(buffer, "%*s %s", uri);

    int length = strlen(uri);
    if (uri[length - 1] == '/') {
        strcpy(uri + length, "index.html");
    }

    try {
        std::string file = get_file_contents(root + (std::string)uri);

        data.result = "HTTP/1.1 200 OK\n";
        data.result += "Content-Type: text/html\n";
        data.result += "Connection: close\n";
        data.result += "Content-Length: " + std::to_string(file.size()) + "\n";
        data.result += "\n";
        data.result += file;

    } catch (int error_id) {
        std::string file = get_file_contents(root + "404.html");

        data.result = "HTTP/1.1 404 NOT_FOUND\n";
        data.result += "Content-Type: text/html\n";
        data.result += "Connection: close\n";
        data.result += "Content-Length: " + std::to_string(file.size()) + "\n";
        data.result += "\n";
        data.result += file;
    }
}


void myparser::send_data(const request_data& data) {
    if (send(data.socket_id, data.result.c_str(), data.result.size(), 0) < 0) {
        perror("send error");
    }
}
