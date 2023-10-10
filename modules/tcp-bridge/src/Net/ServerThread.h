#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include <cstdlib>


#include <thread>
#include <mutex>

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
