#include <string>
#include "http_parser.cpp"


struct Request
{
    std::string method;
    std::string route;
    std::string data;

    void to_request(char* buffer)
    {
        method = parser.parse_method(buffer);
        route = parser.parse_route(buffer);
        data = parser.parse_response_body(buffer);
    }
    
    private:
        HttpParser parser;
};