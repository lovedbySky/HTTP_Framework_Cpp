#include "http_server.cpp"


int main()
{
    HttpServer WebApp;
    WebApp.project_path = "templates/";
    WebApp.using_paths = false;
    WebApp.debug = true;
    WebApp.run(8080);
    return 0;
}
