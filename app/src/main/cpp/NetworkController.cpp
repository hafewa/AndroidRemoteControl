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

void NetworkController::SendMessage(const std::string &message) {
    LogMessage(SendUDPMessage(message));
}

void NetworkController::LogMessage(const std::string &msg)
{
    if(msg.length() > 0 ) {
        mLogIndex = (mLogIndex + 1) % MAX_LOG_SIZE;
        mLog[mLogIndex] = msg;

        mLogSize = MIN(mLogSize+1, MAX_LOG_SIZE);
    }
}

void NetworkController::ClearLog() {
    mLogIndex = 0;
    mLogSize = 0;
}

const std::string& NetworkController::GetLog() const
{
    stringstream s;
    int index = mLogIndex;
    for(int i = 0; i<mLogSize;i++)
    {
        s << mLog[index];

        index = index - 1 < 0 ? MAX_LOG_SIZE - 1 : index -1;
    }

    return std::move(s.str());
}

const string  NetworkController::SendUDPMessage(const string &message)
{
    //send message
    std::string returnString = message;
    if (IsInitialized()) {
        const char *messageCharArray = message.c_str();
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            returnString = "ERROR opening socket\n";
        }
        else if (sendto(sockfd, messageCharArray, message.length(), 0, (struct sockaddr *) &mHostAddress, sizeof(mHostAddress)) < 0) {
            returnString = "sendto() failed\n";
        }
    }
    else{
        returnString += "Host IP or port missing\n";
    }

    return std::move(returnString);
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

    const int port = Helper::parseInteger(data);

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


