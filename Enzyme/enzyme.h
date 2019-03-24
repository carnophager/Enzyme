#ifndef ENZYME_H
#define ENZYME_H

#include "enzyme_global.h"
#include <arpa/inet.h>


class ENZYMESHARED_EXPORT Enzyme
{

private:
    const char * const PORT = "5400";
    int const REQUESTS_BACKLOG_LIMIT = 10;

public:
    Enzyme();
    int initializeSocket();
    void handleSigchild(int signal_number);
    void * getInternetSocketAddress(struct sockaddr * socket_address);
};

#endif // ENZYME_H
