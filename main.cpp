#include "http_framework/http_framework.cpp"


HttpApplication webApp;


void index()
{
    if (request.method == "GET")
    {
        webApp.render_template("index.html"); 
    }
    else if (request.method == "POST")
    {
        logger.console_log(request.data);
        webApp.render_template("index.html"); 
    }
}


void readme()
{
    if (request.method == "GET")
    {
        webApp.render_template("readme.html"); 
    }
}


int main()
{
    config.debug = false;
    config.log = true;
    config.templates_path = "project/";

    webApp.route("/index", index);
    webApp.route("/", index);
    webApp.route("/readme", readme);

    webApp.run("127.0.0.1", 8080);
    return 0;
}
