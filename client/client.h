#ifndef __CLIENT__
#define __CLIENT__

enum ErrorClient
{
    NO_ERROR,
    CREATION_ERROR,
    INVALID_ADDRESS,
    CONNECTION_FAILED
};

class Client
{
public:
    Client();
    Client(int port);
    ~Client();

    /* Connect to the server
    */
    ErrorClient initConnection();

    /*  Handle communication
    */
    void start();

    //TODO
    /*
    */
    void beginSession();

    /*  Send a message to the server
    */
    void message();
    
    /*  Recieve a message from the server
    */
    void recieve();
    
    /*  prints the error message related to the passed value
    */
    void printError(ErrorClient err);
private:
    int fd; // client file descriptor
    int c_socket; // client socket
    int port;
    bool connected; // true if connection is established
    static const int DEFAULT_PORT;
};

#endif//__CLIENT__