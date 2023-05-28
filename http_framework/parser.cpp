#include <string>
#include <regex>


class Parser
{
    public:

        std::string parse_method(char* buff)
        {
            std::string reg = "([\\w\\d]+)\\s+/(.*)";
            std::string route = parse(buff, reg);
            return route;
        }


        std::string parse_user_agent(char* buff)
        {
            std::string str(buff);
            std::regex rgx("User-Agent:\\s+.+");
            std::smatch match;
            std::regex_search(str, match, rgx);
            return match[0].str();
        }
        

        std::string parse_route(char* buff)
        {
            std::string reg = "\\w+\\s+/(\\S+)\\s+HTTP";
            std::string route = parse(buff, reg);
            return route;
        }


        std::string parse_response_body(char* buff)
        {
            std::string reg = "";
            std::string route = parse(buff, reg);
            return route;
        }

    private:
    
        std::string parse(char* buff, std::string reg)
        {
            std::string str(buff);
            std::regex rgx(reg);
            std::smatch match;
            std::regex_search(str, match, rgx);
            return match[1].str();
        }
};
