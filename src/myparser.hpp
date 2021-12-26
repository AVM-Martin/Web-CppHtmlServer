#ifndef MYPARSER_HPP
#define MYPARSER_HPP

#include <string>

#include "mydata.hpp"


namespace myparser {
    void parse_request(const std::string& root, request_data& data);
    void send_data(const request_data& data);
}

#endif
