#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <cstdlib>

#include <thread>

#ifdef WIN32
   #include <thread>
   #include <mutex>
#endif
using namespace std;

class ServerThread {
public:
    std::thread tid;

private:
    static std::mutex mutex;

public:
    ServerThread();

    int Create(void *Callback, void *args);

    int Join();

    static int InitMutex();

    static int LockMutex(const string &identifier);

    static int UnlockMutex(const string &identifier);
};
