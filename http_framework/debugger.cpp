#include <string>
#include <iostream>

// #include "config.cpp"

class Debugger
{
    public:

        void console_log(std::string msg)
        {
            // if (config.debug)
                std::cout << msg << std::endl;
        }

    private:
        // Config config;
};
