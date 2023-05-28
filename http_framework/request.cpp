#include <string>
#include <regex>
#include "parser.cpp"


struct Request
{
    std::string method;
    std::string route;
    std::string data;
    std::string user_agent;

    void to_request(char* buffer)
    {
        method = parser.parse_method(buffer);
        route = parser.parse_route(buffer);
        data = parser.parse_response_body(buffer);
        user_agent = parser.parse_user_agent(buffer);
    }
    
    private:
        Parser parser;
};
