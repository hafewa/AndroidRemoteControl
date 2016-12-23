//
// Created by prith on 12/7/2016.
//

#ifndef ANDROIDREMOTECONTROL_NETWORKMANAGER_H
#define ANDROIDREMOTECONTROL_NETWORKMANAGER_H


#include <cstdint>
#include <string>
#include <linux/in.h>
#include "Saveable.h"

class NetworkController : public Saveable{

public:
    static NetworkController &getInstance();
    NetworkController();
    bool SendUDPMessage(const std::string &message);
    void Init();
    void SetHostAddress(const std::string &ip);
    void SetHostPort(uint16_t port);
    std::string GetCurrentHostIP() const;
    uint16_t GetCurrentHostPort() const;
    bool IsInitialized() const;

    virtual void Save(std::ofstream* file) override ;
private:

    static const int INVALID_PORT = 0;
    sockaddr_in mHostAddress;

    static const std::string mIpAddrKey;
    static const std::string mPortKey;

};


#endif //ANDROIDREMOTECONTROL_NETWORKMANAGER_H
