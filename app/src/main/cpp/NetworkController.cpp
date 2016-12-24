//
// Created by prith on 12/7/2016.
//

#include "NetworkController.h"
#include "helper.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

const std::string NetworkController::mIpAddrKey = "ipaddr";
const std::string NetworkController::mPortKey = "port";

bool NetworkController::SendMessage(const std::string &message) {
    string msgStatus;
    const bool messageSendSuccessful = SendUDPMessage(message, msgStatus);
    LogMessage(msgStatus);
    return messageSendSuccessful;
}

void NetworkController::LogMessage(const std::string &msg)
{
    if(msg.length() > 0 ) {
        mLog[mLogIndex] = msg;

        mLogIndex = static_cast<uint16_t >((mLogIndex + 1) % MAX_LOG_SIZE);
        mLogSize = static_cast<uint16_t >(MIN(mLogSize+1, MAX_LOG_SIZE));
    }
}

void NetworkController::ClearLog() {
    mLogIndex = 0;
    mLogSize = 0;
}

const string NetworkController::GetLog() const
{
    if(mLogSize == 0)
    {
        return " ";
    }

    stringstream s;
    int index = mLogIndex;
    for(int i = 0; i<mLogSize;i++)
    {
        index = index - 1 < 0 ? MAX_LOG_SIZE - 1 : index -1;
        s << mLog[index];
    }

    return std::move(s.str());
}

bool  NetworkController::SendUDPMessage(const string &message, string &status)
{
    //send message
    if (IsInitialized()) {
        const char *messageCharArray = message.c_str();
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            status = "ERROR opening socket\n";
        }
        else if (sendto(sockfd, messageCharArray, message.length(), 0, (struct sockaddr *) &mHostAddress, sizeof(mHostAddress)) < 0) {
            status = "sendto() failed\n";
        }
        else
        {
            status = message;
            return true;
        }
    }
    else{
        status = "Host IP or port missing\n";
    }

    return false;
}

bool NetworkController::IsInitialized() const {
    return (mHostAddress.sin_port != INVALID_PORT) && (mHostAddress.sin_addr.s_addr != 0);
}

NetworkController::NetworkController() : mLogIndex(0), mLogSize(0)
{
    memset(&mHostAddress, 0 , sizeof(mHostAddress));
}

void NetworkController::SetHostAddress(const string &ip)
{
    inet_pton(AF_INET, ip.c_str(), &(mHostAddress.sin_addr));
}

void NetworkController::SetHostPort(uint16_t port)
{
    mHostAddress.sin_port = htons(port);
}

string NetworkController::GetCurrentHostIP() const
{
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(mHostAddress.sin_addr), str, INET_ADDRSTRLEN);

    return str;
}

uint16_t NetworkController::GetCurrentHostPort() const {

    return ntohs(mHostAddress.sin_port);
}

NetworkController& NetworkController::getInstance() {
    static NetworkController controller;
    return controller;
}

void NetworkController::Init()
{
    PersistentDataManager& dataManager = PersistentDataManager::getInstance();

    std::string data = dataManager.GetData(mIpAddrKey);

    if (data.length() > 0)
    {
        SetHostAddress(data);
    }

    data = dataManager.GetData(mPortKey);

    const int port = Helper::to_int(data);

    if(port > 0)
    {
        SetHostPort(static_cast<uint16_t>(port));
    }


}
void NetworkController::Save(std::ofstream *file)
{
    if(file)
    {
        (*file) << mIpAddrKey;
        (*file) << "=";
        (*file) << GetCurrentHostIP();
        (*file) << "\n";

        (*file) << mPortKey;
        (*file) << "=";
        (*file) << Helper::to_string(GetCurrentHostPort());
        (*file) << "\n";
    }
}


