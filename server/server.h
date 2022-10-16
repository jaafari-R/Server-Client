#ifndef __SERVER__
#define __SERVER__

enum ServerError
{

};

/*
    
*/
class Server
{
public:
    // TODO
    Server(int port = DEFAULT_PORT);
    // TODO
    ~Server();

    //TODO
    // TODO replace int with error code
    /*  Opens/starts the server
        The server listens on this->port
    */
    int start();

private:
    //TODO
    /*  Called when an error occurs
    */
    ServerError error(ServerError err);

    //TODO
    void beginSession(int connection_socket);

    //TODO
    /*  Sends a response to the client
    */
    void respond();

    //TODO
    /*  Reads a request from a client
    */
    void recieve();
    
    int port; // the port the server listens on.
    int server_fd; // socket file descriptor that receives and sends requests.
    const static int DEFAULT_PORT;
};

#endif//__SERVER__