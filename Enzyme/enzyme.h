#ifndef ENZYME_H
#define ENZYME_H

#include "enzyme_global.h"

class ENZYMESHARED_EXPORT Enzyme
{

private:
    int const PORT = 5400;
    int const REQUESTS_BACKLOG_LIMIT = 10;

public:
    Enzyme();
    int initializeSocket();
    int initializeSocketBeej();
    void handleSigchild(int signal_number);
    void * getInternetSocketAddress();
};

#endif // ENZYME_H
