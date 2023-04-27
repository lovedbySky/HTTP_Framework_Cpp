#include <iostream>
#include <fstream>
// #include <cstring>
#include <regex>
#include <thread>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class HttpApplication{
    public:
        HttpApplication()
        {
            Config = ConfigApp();
        }

        struct ConfigApp
        {
            std::string secret_key;
            std::string project_path;
            bool debug;
        };

        ConfigApp Config;

        void run(std::string host, int port, bool debug)
        {
            Config.debug = debug;

            int server_socket, client_socket;
            char buffer[1024];
            struct sockaddr_in server_address, client_address;
            server_socket = socket(AF_INET, SOCK_STREAM, 0);
            server_address.sin_family = AF_INET;
            server_address.sin_addr.s_addr = INADDR_ANY;
            server_address.sin_port = htons(port);
            bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
            listen(server_socket, 1);
            std::cout << "Server running on " << host << ':' << port << std::endl;
            while (true) {
                // принятие запроса на соединение
                socklen_t client_address_len = sizeof(client_address);
                client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);

                // чтение данных от клиента
                read(client_socket, buffer, 1024);
                // std::cout << "Received message: " << buffer << std::endl;

                std::string method = this -> parseMethod(buffer);
                std::string route = this -> parseRoute(buffer);
                if (debug) { std::cout << method << " /" << route; }

                if (method == "GET")
                {
                    route = (!route.empty()) ? route : "index.html";
                    if (!Config.project_path.empty()) { Config.project_path += "/"; }
                    std::string response = render_template(Config.project_path + route);
                    write(client_socket, response.c_str(), response.length());
                }
                else
                {
                    std::string response = "HTTP/1.1 404 Error\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n<h1>405 Method Not Allowed</h1>";
                    if (Config.debug) { std::cout << " 405 Method Not Alowed" << std::endl; }
                    write(client_socket, response.c_str(), response.length());
                }
                close(client_socket);
            }
            close(server_socket);
        }
    private:

        std::string render_template(std::string path)
        {
            std::ifstream file(path);
            std::string response;
            if (file.is_open())
            {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                response = "HTTP/1.1 200 OK\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n" + content;
                if (Config.debug) { std::cout << " 200 OK" << std::endl; }
            }
            else
            {
                response = "HTTP/1.1 404 Error\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n<h1>404 Page Not Found</h1>";
                if (Config.debug) { std::cout << " 404 Page Not Found" << std::endl; }
            }
            return response;
        }


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