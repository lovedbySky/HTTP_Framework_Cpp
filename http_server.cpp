#include <iostream>
#include <fstream>
// #include <cstring>
#include <regex>
#include <thread>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class HttpServer{
    public:

        std::string templates_path = "templates/";
        bool using_paths = true;
        bool debug = false;


        void run(int port)
        {
            int server_socket, client_socket;
            char buffer[1024];
            struct sockaddr_in server_address, client_address;
            server_socket = socket(AF_INET, SOCK_STREAM, 0);
            server_address.sin_family = AF_INET;
            server_address.sin_addr.s_addr = INADDR_ANY;
            server_address.sin_port = htons(port);
            bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
            listen(server_socket, 1);
            std::cout << "Server running on port 8080" << std::endl;
            while (true) {
                // принятие запроса на соединение
                socklen_t client_address_len = sizeof(client_address);
                client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);

                // чтение данных от клиента
                read(client_socket, buffer, 1024);
                // std::cout << "Received message: " << buffer << std::endl;

                std::string filename = this -> parsePath(buffer);
                if (debug) { std::cout << "GET /" << filename; }

                // чтение файла
                
                filename = (!filename.empty()) ? filename : "index.html";
                std::ifstream file(templates_path + filename);
                std::string response;
                if (file.is_open())
                {
                    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                    response = "HTTP/1.1 200 OK\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n" + content;
                    if (debug) { std::cout << " 200 OK" << std::endl; }
                }
                else
                {
                    response = "HTTP/1.1 404 Error\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n<h1>Page not found</h1>";
                    if (debug) { std::cout << " 404 Error" << std::endl; }
                }
                
                write(client_socket, response.c_str(), response.length());

                // закрытие соединения с клиентом
                close(client_socket);
            }

            // закрытие серверного сокета
            close(server_socket);
        }
    private:

        std::string parseMethod(char* buff);
        std::string parseUserAgent(char* buff);
        std::string parsePath(char* buff)
        {
            std::string str(buff);
            std::regex rgx("GET\\s+/(\\S+)\\s+HTTP");
            std::smatch match;
            std::regex_search(str, match, rgx);
            return match[1].str();
        }

};
