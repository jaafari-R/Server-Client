#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

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
    
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if(this->sock < 0)
    {
        // socket creation error
        return SOCKET_FAILED_ERROR;
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
    this->fd = connect(this->sock, (sockaddr *) &server_addr, sizeof(server_addr));
    if(this->fd < 0)
    {
        // connection failed
        return CONNECTION_FAILED;
    }
    
    return NO_ERROR;
}

void Client::beginSession()
{
    Buffer buffer(this->buffer_size);
    std::string request;  // received request
    std::string response; // response to the requester

    request = "Test Request";

    this->sendRequest(request);
    response = this->recieve(buffer);
    this->handleResponse(response);

    close(this->fd);
}

void Client::sendRequest(std::string request)
{
    int send_val;
    Buffer request_buffer(request.size());
    request_buffer.write(request);

    send_val = send(this->sock, request_buffer.getBuffer(), request_buffer.getSize(), 0);

    /* TODO add send_val check for erros & other information */
}

std::string Client::recieve(Buffer& buffer)
{
    int read_val; // number of bytes read from the socket
    
    read_val = read(sock, buffer.getBuffer(), buffer.getSize());

    /* TODO add read_val check for errors & other information */

    return buffer.read();
}

void Client::handleResponse(std::string response)
{
    std::cout << "Received from server: " << response << std::endl;
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