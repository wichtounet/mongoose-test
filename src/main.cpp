#include <cstdlib>

#include <unistd.h>
#include <signal.h>

#include <mongoose/Server.h>
#include <mongoose/WebController.h>

//Unfortunately these lines are mandatory because of poor coding of the binding
using namespace std;
using namespace Mongoose;

struct hello_controller : public WebController {
    void hello(Request& request, StreamResponse& response){
        response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << std::endl;
    }

    void display(Request& /*request*/, StreamResponse& response){
        response << "<html><head><title>Test</title></head><body><h1>Hello you!</h1><div>This is a web page generated in C++ and I'm proud of it :P</div></html>" << std::endl;
    }

    //This will be called automatically
    void setup(){
        addRoute("GET", "/hello", hello_controller, hello);
        addRoute("GET", "/display", hello_controller, display);
    }
};

int main(){
    // Create the controller handling the requests
    hello_controller controller;

    // Run the server with our controller
    Server server(8080);
    server.registerController(&controller);

    // Start the server and wait forever
    server.start();

    //Simple stupid infinite loop to wait
    while (1) {
        sleep(10);
    }
}
