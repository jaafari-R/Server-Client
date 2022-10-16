#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"

const int Client::DEFAULT_PORT = 17284;

Client::Client()
{
    this->port = this->DEFAULT_PORT;
}

Client::Client(int port)
{
    connected = false;
    if(port < 0 && port > 65535) 
        this->port = this->DEFAULT_PORT;
    else
        this->port = port;

}

Client::~Client() {}

ErrorClient Client::initConnection()
{
    /* initialize socket */
    struct sockaddr_in server_addr;
    
    this->c_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(this->c_socket < 0)
    {
        // socket creation error
        return CREATION_ERROR;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->port);
    
    // Convert IPv4 address from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        // invalid address
        return INVALID_ADDRESS;
    }
    
    /* Connect to Server */
    this->fd = connect(this->c_socket, (sockaddr *) &server_addr, sizeof(server_addr));
    if(this->fd < 0)
    {
        // connection failed
        return CONNECTION_FAILED;
    }
    
    return NO_ERROR;
}

void Client::beginSession()
{
    int valread;
    const char* request = "This is a Request!";
    char buffer[1024] = {0};
    
    send(this->c_socket, request, strlen(request), 0);
    printf("Hello message sent\n");
    valread = read(this->c_socket, buffer, 1024);
    printf("%s\n", buffer);

    close(this->fd);
}

void Client::printError(ErrorClient err)
{
    switch(err)
    {
        case NO_ERROR:
            break;
        case CREATION_ERROR:
            break;
        case INVALID_ADDRESS:
            break;
        case CONNECTION_FAILED:
            break;
    }
}