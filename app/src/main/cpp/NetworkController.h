//
// Created by prith on 12/7/2016.
//

#ifndef ANDROIDREMOTECONTROL_NETWORKMANAGER_H
#define ANDROIDREMOTECONTROL_NETWORKMANAGER_H


#include <cstdint>
#include <string>
#include <linux/in.h>

class NetworkController {

public:
    NetworkController();
    bool SendUDPMessage(std::string &message);

    void SetHostAddress(std::string & ip);
    void SetHostPort(uint16_t port);
    std::string GetCurrentHostIP() const;
    uint16_t GetCurrentHostPort() const;
    bool IsInitialized() const;
private:

    static const int INVALID_PORT = 0;
    sockaddr_in mHostAddress;
};


#endif //ANDROIDREMOTECONTROL_NETWORKMANAGER_H
