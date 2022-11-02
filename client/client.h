#ifndef __CLIENT__
#define __CLIENT__
#include "../utils/buffer.h"

enum ErrorClient
{
    NO_ERROR,
    UNKNOWN_ERROR,
    SOCKET_FAILED_ERROR,
    INVALID_ADDRESS,
    CONNECTION_FAILED
};
const static char* CLIENT_ERROR_MESSAGES[] = 
{
    "", // NO_ERROR
    "An unknown error has occured!", // UNKNOWN_ERROR
    "An error has occured while creating the socket!", // SOCKET_FAILED_ERROR
    "Invalid server ip address format!",// INVALID_ADDRESS
    "An error has occured while trying to connect to the server!"// CONNECTION_FAILED
};


class Client
{
public:
    // TODO
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

    /*  Send a request to the server
    */
    void sendRequest(std::string request);
    /*  Recieve a response from the server
    */
    std::string recieve(Buffer& buffer);
    
    /* Perform an action based on the received response
    */
    void handleResponse(std::string response);

    /*  prints the error message related to the passed value
    */
    void printError(ErrorClient err);
private:
    int fd; // client file descriptor
    int sock; // client socket
    int port;
    bool connected; // true if connection is established
    int buffer_size; // server response buffer size
    static const int DEFAULT_PORT;
};

#endif//__CLIENT__