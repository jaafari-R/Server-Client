#ifndef __SERVER__
#define __SERVER__

enum ServerError
{
    NO_ERROR = 0,
    UNKNOWN_ERROR,
    SOCKET_FAILED_ERROR,
    SET_SOCK_OPTION_ERROR,
    SOCK_BIND_ERROR,
    SOCK_LISTEN_ERROR,
    SOCK_ACCEPT_ERROR,
};
const char* ERROR_MESSAGES[] = 
{
    "", // NO_ERROR
    "An Unknown Error Has Occured!", // UNKNOWN_ERROR
    "", // SOCKET_FAILED_ERROR
    "", // SET_SOCK_OPTION_ERROR
    "", // SOCK_BIND_ERROR
    "", // SOCK_LISTEN_ERROR
    "", // SOCK_ACCEPT_ERROR
};

/*
    
*/
class Server
{
public:
    // TODO
    Server(int port = DEFAULT_PORT, int buffer_size = DEFAULT_BUFFER_SIZE);
    // TODO
    ~Server();

    //TODO
    // TODO replace int with error code
    /*  Opens/starts the server
        The server listens on this->port
    */
    int start();

private:
    /*  Receives an error prints & returns it
    */
    ServerError error(ServerError err);

    /*  Print error message
    */
    void printError(ServerError err);

    //TODO
    void beginSession(int connection_socket);

    //TODO
    /*  Reads a request from a client
    */
    std::string recieve(int sock, char buffer[]);

    //TODO
    /*  Sends a response to the client
    */
    void respond();
    
    int port; // the port the server listens on.
    int server_fd; // socket file descriptor that receives and sends requests.
    char* buffer;
    int buffer_size;
    const static int DEFAULT_BUFFER_SIZE;
    const static int DEFAULT_PORT;
};

#endif//__SERVER__