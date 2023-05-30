#include "http_framework/http_framework.cpp"


HttpApplication webApp;


void index();
void login();
void readme();


int main()
{
    config.debug = true;
    config.log = false;
    config.templates_path = "project/";

    webApp.route("/index", index);
    webApp.route("/", index);
    webApp.route("/readme", readme);
    webApp.route("/login", login);


    webApp.run("127.0.0.1", 8080);
    return 0;
}


void index()
{
    // localhost:port/index
    webApp.render_template("index.html");
}


void login()
{
    // localhost:port/login
    if (request.method == "GET")
    {
        webApp.render_template("login.html"); 
    }
    else if (request.method == "POST")
    {
        if (request.data.find("admin") != std::string::npos and request.data.find("12345") != std::string::npos)
            webApp.render_template("index.html");
        else
            webApp.render_template("login.html"); 
    }
}


void readme()
{
    // localhost:port/readme
    webApp.render_template("readme.html"); 
}
