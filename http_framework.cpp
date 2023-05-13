#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <map>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class HttpApplication;


struct Config
{
    std::string secret_key;
    std::string templates_path;
    bool debug;
};

struct Request
{
    std::string method;
    std::string route;
};


class HttpApplication
{
    public:
        HttpApplication()
        {
            config = Config();
            request = Request();
        }

        Config config;
        Request request;
        int server_socket, client_socket;

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
                // if (config.debug) { std::cout << " 200 OK" << std::endl; }
            }
            else
            {
                response = "HTTP/1.1 404 Error\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n<h1>404 Page Not Found</h1>";
                // if (config.debug) { std::cout << " 404 Page Not Found" << std::endl; }
            }
            // return response;
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
            if (config.debug) { std::cout << "Debug mode is on" << std::endl; }
            else { std::cout << "Debug mode is off" << std::endl; }
            while (true) {
                // принятие запроса на соединение
                socklen_t client_address_len = sizeof(client_address);
                client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);

                // чтение данных от клиента
                read(client_socket, buffer, 1024);
                // std::cout << "Received message: " << buffer << std::endl;

                request.method = parseMethod(buffer);
                request.route = parseRoute(buffer);
                // if (config.debug) { std::cout << request.method << " /" << route; }

                if (routes.count(request.route) != 0)
                {
                    routes[request.route]();
                    if (config.debug) { std::cout << "/" << request.route << " 200 OK" << std::endl; }
                }
                else
                {
                    std::string response = "HTTP/1.1 404 Error\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n<h1>404 Page Not Found</h1>";
                    if (config.debug) { std::cout << "/" << request.route << " 404 Page Not Found" << std::endl; }
                    write(client_socket, response.c_str(), response.length());
                }
                
                close(client_socket);
            }
            close(server_socket);
        }

    private:
        std::map <std::string, void(*)()> routes;

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
