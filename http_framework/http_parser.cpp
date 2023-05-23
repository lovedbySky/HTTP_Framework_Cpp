#include <regex>


class HttpParser
{
    public:
        std::string parseMethod(char* buff)
        {
            std::string str(buff);
            std::regex rgx("([\\w\\d]+)\\s+/(.*)");
            std::smatch match;
            std::regex_search(str, match, rgx);
            return match[1].str();
        }


        std::string parseUserAgent(char* buff)
        {
            std::string str(buff);
            std::regex rgx("User-agent:\\s+/(\\S+)\\s");
            std::smatch match;
            std::regex_search(str, match, rgx);
            return match[1].str();
        }
        

        std::string parseRoute(char* buff)
        {
            std::string str(buff);
            std::regex rgx("\\w+\\s+/(\\S+)\\s+HTTP");
            std::smatch match;
            std::regex_search(str, match, rgx);
            return match[1].str();
        }
};
