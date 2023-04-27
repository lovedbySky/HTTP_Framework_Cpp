#include "http_framework.cpp"


int main()
{
    HttpApplication WebApp;

    WebApp.Config.secret_key = "12345";
    // WebApp.Config.project_path = "project/";

    WebApp.run("127.0.0.1", 9090, true);
    return 0;
}
