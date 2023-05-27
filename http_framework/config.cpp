#include <string>

struct Config
{
    std::string secret_key;
    std::string templates_path;
    bool debug;
    bool log;
};
