#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> // close()

#include <iostream>

#include "server.h"
#include "../utils/buffer.h"

const int Server::DEFAULT_PORT = 17284;
const static int DEFAULT_BUFFER_SIZE = 1024;

Server::Server(int port, int buffer_size)
{
    // set port
    if(port < 0 && port > 65535) 
        this->port = this->DEFAULT_PORT;
    else
        this->port = port;
    // set buffer size
    if(buffer_size < 0)
        this->buffer_size = DEFAULT_BUFFER_SIZE;
    else
        this->buffer_size = buffer_size;
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
        return this->error(SOCKET_FAILED_ERROR);

    // Set Server Socket to be reusable
    reusable = setsockopt(this->server_fd, SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT, &reuse_val, sizeof(reuse_val));

    if(reusable)
        this->error(SET_SOCK_OPTION_ERROR); // TODO add eror

    // Setup the socket address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port);

    /* Bind Server Socket */
    if(bind(this->server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
        this->error(SOCK_BIND_ERROR);

    /* Listen for Connections */
    if (listen(this->server_fd, 15) < 0)
        this->error(SOCK_LISTEN_ERROR);

    /* Accept Connection */
    connection_socket = accept(this->server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (connection_socket < 0)
        this->error(SOCK_ACCEPT_ERROR); // TODO add eror
    
    this->beginSession(connection_socket);

    /* Close Server */
    shutdown(server_fd, SHUT_RDWR);

    return 0; // TODO add error code for return
}


void Server::beginSession(int connection_socket)
{
    Buffer buffer(this->buffer_size);
    std::string request;  // received request
    std::string response; // response to the requester

    request = this->recieve(connection_socket, buffer);

    this->respond(connection_socket, response);

    // closing the connected socket
    close(connection_socket);
}

std::string Server::recieve(int sock, Buffer& buffer)
{
    int read_val; // number of bytes read from the socket
    
    read_val = read(sock, buffer.getBuffer(), buffer.getSize());

    /* TODO add read_val check for errors & other information */

    return buffer.read();
}

void respond(int sock, std::string response)
{
    int send_val;
    Buffer response_buffer(response.size());
    response_buffer.write(response);

    send_val = send(sock, response_buffer.getBuffer(), response_buffer.getSize(), 0);

    /* TODO add send_val check for erros & other information */
}

ServerError Server::error(ServerError err)
{
    this->printError(err);
    return err;
}

void Server::printError(ServerError err)
{
    std::cerr << ERROR_MESSAGES[static_cast<int>(err)] << std::endl;
}