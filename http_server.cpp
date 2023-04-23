#include <iostream>
#include <fstream>
// #include <cstring>
#include <regex>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


class HttpServer{
    public:
        
        bool using_paths = true;
        bool debug = false;

        static void run(int port)
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
                std::cout << "Received message: " << buffer << std::endl;

                // чтение файла
                const char* filename = "templates/index.html";
                std::ifstream file(filename);
                if (!file.is_open()) {
                    std::cerr << "Error opening file " << filename << std::endl;
                    // return 1;
                }
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                // отправка данных клиенту
                std::string response = "HTTP/1.1 200 OK\r\nServer: Ivan\r\nContent-Type: text/html\r\n\r\n" + content;
                write(client_socket, response.c_str(), response.length());

                // закрытие соединения с клиентом
                close(client_socket);
            }

            // закрытие серверного сокета
            close(server_socket);
        }
    private:
        
};

