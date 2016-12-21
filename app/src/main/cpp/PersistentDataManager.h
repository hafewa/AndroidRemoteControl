//
// Created by prith on 12/7/2016.
//

#ifndef ANDROIDREMOTECONTROL_PERSISTENTDATAMANAGER_H
#define ANDROIDREMOTECONTROL_PERSISTENTDATAMANAGER_H


#include <string>

class PersistentDataManager {

public:
    static PersistentDataManager& getInstance();
    void setDataFile(std::string& path);

    void LoadPersistentData();
    void SavePersistentData();

private:
    PersistentDataManager();
    std::string mDataFilePath;
    std::string mTargetHost;
    uint16_t mTargetPort;
};


#endif //ANDROIDREMOTECONTROL_PERSISTENTDATAMANAGER_H
