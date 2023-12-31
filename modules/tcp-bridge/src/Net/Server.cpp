#include "Server.h"

#ifdef WIN32
   #define NOMINMAX
   #include <ws2tcpip.h>
   #include <BaseTsd.h>
   using  ssize_t = SSIZE_T;
#endif

using namespace std;

vector<Client> Server::clients;

Server::Server(int port) {

    // Initialize static mutex from ServerThread
    ServerThread::InitMutex();

    // For setsock opt (REUSEADDR)
#ifdef WIN32
    const char yes = 0x01;
#else
    int yes = 1;
#endif
    m_runThread = true;

    // Init serverSock and start listen()'ing
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    setsockopt(serverSock, IPPROTO_TCP, TCP_NODELAY, (char *) &yes, sizeof(int));



    if (bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0)
        cerr << "Failed to bind";

    listen(serverSock, 30);
}

void Server::AcceptAndDispatch() {

    Client *c;
    ServerThread *t;

    socklen_t cliSize = sizeof(sockaddr_in);

    while (m_runThread) {

        c = new Client();
        t = new ServerThread();

        // Blocks here;
        c->sock = accept(serverSock, (struct sockaddr *) &clientAddr, &cliSize);
        if (c->sock < 0) {
            cerr << "Error on accept";
        } else {
            t->Create((void *) Server::HandleClient, c);
        }
    }
}

void Server::SendToAll(const std::string &message) {
    ssize_t n;

    ServerThread::LockMutex("'SendToAll()'");

    for (auto &client : clients) {
        n = send(client.sock, message.c_str(), strlen(message.c_str()), 0);
        // cout << n << " bytes sent." << endl;
    }

    // Release the lock
    ServerThread::UnlockMutex("'SendToAll()'");
}

void Server::SendToAll(char *message) {
    ssize_t n;

    // Acquire the lock
    ServerThread::LockMutex("'SendToAll()'");

    for (auto &client : clients) {
        n = send(client.sock, message, strlen(message), 0);
        // cout << n << " bytes sent." << endl;
    }

    // Release the lock
    ServerThread::UnlockMutex("'SendToAll()'");
}

void Server::SendToClient(Client *c, const std::string &message) {
    ssize_t n;
    ServerThread::LockMutex("'SendToClient()'");

    // cout << " Sending message to [" << c->name << "](" << c->id << "): " <<
    // message << endl;
    n = send(c->sock, message.c_str(), strlen(message.c_str()), 0);
    // cout << n << " bytes sent." << endl;
    ServerThread::UnlockMutex("'SendToClient()'");
}

void Server::ListClients() {
    for (auto &client : clients) {
        cout << "|" << client.name << "|" << client.clientType << endl;

    }
}

/*
  Should be called when vector<Client> clients is locked!
*/
int Server::FindClientIndex(Client *c) {
    for (size_t i = 0; i < clients.size(); i++) {
        if ((Server::clients[i].id) == c->id)
            return (int) i;
    }
    cerr << "Client id not found." << endl;
    return -1;
}

Client *Server::GetClientByIndex(std::string id) {
    for (size_t i = 0; i < clients.size(); i++) {
        if ((Server::clients[i].id) == id)
            return &Server::clients[i];
    }
    return nullptr;
}
