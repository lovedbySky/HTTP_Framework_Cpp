#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <map>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "debugger.cpp"
#include "config.cpp"
#include "request.cpp"


Debugger debug;
Config config;
Request request;


class HttpApplication
{
    public:
        void route(std::string route, void (&func)())
        {
            route.erase(route.find("/"), 1);
            routes[route] = func; 
        }

        void render_template(std::string path)
        {
            std::ifstream file(config.templates_path + path);
            std::string response;
            if (file.is_open())
            {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                response = "HTTP/1.1 200 OK\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n" + content;
            }
            else
            {
                response = "HTTP/1.1 404 Error\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n<h1>404 Page Not Found</h1>";
            }
            write(client_socket, response.c_str(), response.length());
        }

        void run(std::string host, int port)
        {
            char buffer[1024];
            struct sockaddr_in server_address, client_address;
            server_socket = socket(AF_INET, SOCK_STREAM, 0);
            server_address.sin_family = AF_INET;
            server_address.sin_addr.s_addr = INADDR_ANY;
            server_address.sin_port = htons(port);
            bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
            listen(server_socket, 1);
            std::cout << "Server running on " << host << ':' << port << std::endl;
            if (config.debug) { debug.console_log("Debug mode is on"); }
            else { debug.console_log("Debug mode is off"); }
            while (true) {
                // принятие запроса на соединение
                socklen_t client_address_len = sizeof(client_address);
                client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);

                // чтение данных от клиента
                read(client_socket, buffer, 1024);

                request.to_request(buffer);

                if (routes.count(request.route) != 0)
                {
                    routes[request.route]();
                    debug.console_log("/" + request.route + " 200 OK");
                }
                else
                {
                    std::string response = "HTTP/1.1 404 Error\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n<h1>404 Page Not Found</h1>";
                    write(client_socket, response.c_str(), response.length());
                    debug.console_log("/" + request.route + " 404 Page Not Found");
                }
                
                close(client_socket);
            }
            close(server_socket);
        }

    private:
        int server_socket, client_socket;
        std::map <std::string, void(*)()> routes;
};
