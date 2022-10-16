#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> // close()

#include <iostream>

#include "server.h"

const int Server::DEFAULT_PORT = 17284;

Server::Server(int port)
{
    if(port < 0 && port > 65535) 
        this->port = this->DEFAULT_PORT;
    else
        this->port = port;
}

Server::~Server(){}


int Server::start()
{
    /* Initialize Server Socket*/
    int connection_socket;
    int reusable; //
    int reuse_val = 1; //
    struct sockaddr_in address; // 
    int addrlen = sizeof(address);

    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(this->server_fd < 0)
    {
        this->error(); // TODO add eror
        return -1; // TODO return error code 
    }

    // Set Server Socket to be reusable
    reusable = setsockopt(this->server_fd, SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT, &reuse_val, sizeof(reuse_val));

    if(reusable)
    {
        this->error(); // TODO add eror
        return -1; // TODO return error code 
    }

    // Setup the socket address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port);

    /* Bind Server Socket */
    if(bind(this->server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        this->error(); // TODO add eror
        return -1; // TODO return error code 
    }

    /* Listen for Connections */
    if (listen(this->server_fd, 15) < 0)
    {
        this->error(); // TODO add eror
        return -1; // TODO return error code 
    }

    /* Accept Connection */
    connection_socket = accept(this->server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (connection_socket < 0)
    {
        this->error(); // TODO add eror
        return -1; // TODO return error code 
    }
    
    this->beginSession(connection_socket);

    /* Close Server */
    shutdown(server_fd, SHUT_RDWR);

    return 0; // TODO add error code for return
}


void Server::beginSession(int connection_socket)
{
    int valread;
    char buffer[1024] = {0};
    const char* response = "This is a response!";

    valread = read(connection_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(connection_socket, response, strlen(response), 0);
    printf("Hello message sent\n");
 
    // closing the connected socket
    close(connection_socket);
}

ServerError Server::error(ServerError err)
{
    switch(err)
    {
    default:
        std::cerr << "An Unknown Error Error!";
        break;
    }
    return err;
}