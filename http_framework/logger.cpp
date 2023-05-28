#include <string>
#include <fstream>


class Logger
{
    public:

        void console_log(std::string msg)
        {
            std::cout << msg << std::endl;
        }


        void access_log(std::string info)
        {
            write_to_file("log/access.log", info);
        }


        void error_log(std::string error)
        {
            write_to_file("log/error.log", error);
        }

    private:

        void write_to_file(std::string path, std::string msg)
        {
            std::ofstream file(path, std::ios::app);
            if (file.is_open())
                file << msg << std::endl;
            file.close();
        }
};
