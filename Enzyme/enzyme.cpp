#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <netinet/in.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

#include "enzyme.h"

Enzyme::Enzyme()
{
    std::cout << "Hello, enzo!" << std::endl;
    this->initializeSocket();
    //sockaddr asdf();
    //getaddrinfo()
    //this->initializeSocket();
}

void Enzyme::handleSigchild(int signal_number)
{
    //waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while( waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

//get sockaddr, IPv4 or IPv6:
void * Enzyme::getInternetSocketAddress(struct sockaddr * socket_address)
{
    if ( socket_address->sa_family == AF_INET ) //IPv4
    {
        return &(((struct sockaddr_in*) socket_address)->sin_addr);
    } else {
        return &(((struct sockaddr_in6*) socket_address)->sin6_addr);
    }
}

int Enzyme::initializeSocket()
{
    int socket_file_descriptor; // listen on socket_file_descriptor
    int new_socket_file_descriptor; // new connection on new_socket_file_descriptor

    struct addrinfo hints;
    struct addrinfo * server_address_information;
    struct addrinfo * p;

    struct sockaddr_storage their_addr; // connector's address information

    socklen_t sin_size;
    struct sigaction signal_action;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use local ip

    if ( (rv == getaddrinfo(NULL, this->PORT, &hints, &server_address_information)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for ( p = server_address_information; p != NULL; p = p->ai_next )
    {
        if ( (socket_file_descriptor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1  )
        {
            perror("server: socket");
            continue;
        }

        if ( setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if ( bind(socket_file_descriptor, p->ai_addr, p->ai_addrlen) == -1 )
        {
            close(socket_file_descriptor);
            perror("server: bind");
            continue;
        }

        break; //We found a result that satisfies all conditions
    }

    freeaddrinfo(server_address_information); //server_address_information is no longer needed
}

#if 0
int Enzyme::initializeSocket()
{
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if ( listening == -1 )
    {
        std::cerr << "Can't create a socket!";
        return -1;
    }

    // Bind the socket to a IP / port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(5401);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); // 127.0.0.1

    if ( bind(listening, (sockaddr *) &hint, sizeof(hint)) == -1 )
    {
        std::cerr << "Can't bind to IP/port";
        return -2;
    }

    // Mark the socket for listening in
    int listening_result = listen(listening, SOMAXCONN);
    std::cout << "listen(listening, SOMAXCONN) result: listening_result" << std::endl;
    if ( listening_result == -1)
    {
        std::cerr << "Cant' listen!";
        return -3;
    }
    std::cout << "service(NI_MAXSERV)" << std::endl;

    // Accept a call
    sockaddr_in client;
    socklen_t clientSize;
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    std::cout << "service(NI_MAXSERV)" << std::endl;

    int clientSocket;
    while(true)
    {
        //clientSocket = accept(listening, (sockaddr *)&client, &clientSize);
        std::cout << "after accept(NI_MAXSERV)" << std::endl;
    }

    if ( clientSocket == -1)
    {
        std::cerr << "Problem with client connecting!";
        return -4;
    }

    std::cout << "service(NI_MAXSERV)" << std::endl;

    // Close the listening socket
    close(listening);
    std::cout << "close(listening)" << std::endl;

    memset(host , 0, NI_MAXHOST);
    memset(service  , 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0);

    if (result )
    {
        std::cout << host << " connected on " << service << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << "connected on " << ntohs(client.sin_port) << std::endl;
    }

    // While receiving - display message, echo message
    const int buffer_size = 4096;
    char buf[buffer_size];
    while (true)
    {
        // Clear the buffer
        memset(buf, 0, buffer_size);
        // Wait for a message
        int bytesRecv = recv(clientSocket, buf, buffer_size, 0);

        if (bytesRecv == -1)
        {
            std::cerr << "There was a connection issue" << std::endl;
            break;
        }

        if ( bytesRecv == 0 )
        {
            std::cout << "The client disconnected" << std::endl;
            break;
        }

        // Display message
        std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;

        std::cout << "int(buf[1]): " << int(buf[1]) << std::endl;

        //char selsko[] = "HTTP/1.1 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nServer: Apache/2.2.3\nContent-Type: text/html charset=utf-8\nContent-Length: 262\nAccept-Ranges: bytes\nConnection: close\n\n<html> <meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\"> <body><h1>Ето ги, те са туук!<img src=\"https://vignette.wikia.nocookie.net/citv/images/6/67/Adventures_of_the_Gummi_Bears.jpg/revision/latest?cb=20180203235857\" /></h1></body></html>";
        char selsko[] = "HTTP/1.1 200 OK\nDate: Thu, 19 Feb 2009 12:27:04 GMT\nServer: Apache/2.2.3\nLast-Modified: Wed, 18 Jun 2003 16:05:58 GMT\nETag: \"56d-9989200-1132c580\"\nContent-Type: text/html\nContent-Length: 260\nAccept-Ranges: bytes\nConnection: close\n\n<html><meta http-equiv='Content-Type' content='text/html;charset=utf-8'><body><h1>Ето ги, те са туук!<br /><img src='https://vignette.wikia.nocookie.net/citv/images/6/67/Adventures_of_the_Gummi_Bears.jpg/revision/latest?cb=20180203235857'></h1></body></html>";
        char *reply =
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "Server: Apache/2.2.3\n"
        "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: 260\n"
        "Accept-Ranges: bytes\n"
        "Connection: close\n"
        "\n"
        "<html><meta http-equiv='Content-Type' content='text/html;charset=utf-8'><body><h1>Ето ги, те са туук!<br /><img src='https://vignette.wikia.nocookie.net/citv/images/6/67/Adventures_of_the_Gummi_Bears.jpg/revision/latest?cb=20180203235857' /></h1></body></html>";

        size_t size = strlen(selsko);

        /*
        char new_village[buffer_size];
        char s = char(13);
        memset(new_village, 0, buffer_size);
        int initialBytesRecv = bytesRecv;
        int pos = 0;
        for ( int i = 0; i < initialBytesRecv - 2; ++i)
        {
           //++bytesRecv;
           new_village[i] = buf[i];
           ++pos;
        }
        new_village[pos] = ' ';
        new_village[pos + 1] = 's';
        new_village[pos + 2] = 'e';
        new_village[pos + 3] = 'n';
        new_village[pos + 4] = 'd';
        new_village[pos + 5] = '\n';
        */
        send(clientSocket, selsko, size, 0);

        /*
        for (int c=3; c>0; --c) {
          std::cout << c << std::endl;
          std::this_thread::sleep_for (std::chrono::seconds(1));
        }
        */


        // Resend message
        send(clientSocket, selsko, size, 0);
    }

    // Close socket
    close(clientSocket);
   //ininitializeSocket();

    return 0;
}

#endif
