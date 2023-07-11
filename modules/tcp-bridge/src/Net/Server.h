#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef WIN32
   #define NOMINMAX
   #include <WinSock2.h>
#else
   #include <netinet/in.h>
   #include <netinet/tcp.h>
   #include <sys/socket.h>
#endif

#include "Client.h"
#include "ServerThread.h"

using namespace std;

class Server {

private:
    static vector<Client> clients;
    int serverSock;
    struct sockaddr_in serverAddr, clientAddr;

public:
    explicit Server(int port);

    void AcceptAndDispatch();

    static void *HandleClient(void *args);

    static void SendToAll(const std::string &message);

    static void SendToClient(Client *c, const std::string &message);

    static Client *GetClientByIndex(std::string id);

private:
    static void ListClients();

    static void SendToAll(char *message);

    static int FindClientIndex(Client *c);

protected:
    bool m_runThread;
};

