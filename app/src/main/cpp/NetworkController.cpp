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

bool NetworkController::SendUDPMessage(const string &message)
{
    //send message
    if (IsInitialized()) {
        const char *messageCharArray = message.c_str();
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            perror("ERROR opening socket");
            return false;
        }

        if (sendto(sockfd, messageCharArray, message.length(), 0, (struct sockaddr *) &mHostAddress, sizeof(mHostAddress)) < 0) {
            perror("sendto() failed");
            return false;
        }
        return true;
    }
    else{
        return false;
    }

}

bool NetworkController::IsInitialized() const {
    return (mHostAddress.sin_port != INVALID_PORT) && (mHostAddress.sin_addr.s_addr != 0);
}

NetworkController::NetworkController()
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

