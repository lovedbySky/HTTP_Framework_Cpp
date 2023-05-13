#include "http_framework.cpp"


HttpApplication WebApp;


void index()
{
    if (WebApp.request.method == "GET")
    {
        WebApp.render_template("index.html"); 
    }
}


void readme()
{
    if (WebApp.request.method == "GET")
    {
        WebApp.render_template("readme.html"); 
    }
}


int main()
{
    WebApp.config.debug = true;
    WebApp.config.secret_key = "12345";
    WebApp.config.templates_path = "project/";

    WebApp.route("/index", index);
    WebApp.route("/", index);
    WebApp.route("/readme", readme);

    WebApp.run("127.0.0.1", 8080);
    return 0;
}
