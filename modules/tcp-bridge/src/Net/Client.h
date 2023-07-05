#pragma once

#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

#define MAX_NAME_LENGTH 40

class Client {
public:
    std::string id;
    std::string name;
    std::string uuid;
    std::string clientType;

    bool keepHistory = false;

    // Socket stuff
    int sock{};

    Client() {};

    void SetId(std::string id);

    void SetName(std::string &name);

    void SetUUID(std::string &uuid);

    void SetClientType(std::string &clientType);

    void SetKeepHistory(bool historyflag);
};

