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
    void SendMessage(const std::string& message);
    void Init();
    void SetHostAddress(const std::string &ip);
    void SetHostPort(uint16_t port);
    std::string GetCurrentHostIP() const;
    uint16_t GetCurrentHostPort() const;
    bool IsInitialized() const;
    const std::string& GetLog() const;
    void ClearLog();
    virtual void Save(std::ofstream* file) override ;
private:

    NetworkController();
    const std::string  SendUDPMessage(const std::string &message);
    void LogMessage(const std::string& msg);
    static const int INVALID_PORT = 0;
    sockaddr_in mHostAddress;

    static const std::string mIpAddrKey;
    static const std::string mPortKey;
    static const uint16_t MAX_LOG_SIZE = 1024;

    std::string mLog[MAX_LOG_SIZE];
    uint16_t mLogIndex;
    uint16_t mLogSize;

};


#endif //ANDROIDREMOTECONTROL_NETWORKMANAGER_H
