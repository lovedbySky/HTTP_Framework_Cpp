#include "http_server.cpp"


int main()
{
    HttpServer WebApp;
    WebApp.using_paths = false;
    WebApp.debug = false;
    WebApp.run(8080);
    return 0;
}
