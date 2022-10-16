#include "client.h"
#include "stdio.h"

int main()
{
    Client client;
    ErrorClient ce;
    ce = client.initConnection();
    if(ce == NO_ERROR)
        client.beginSession();
    else
        printf("%d\n", ce);
    return 0;
}