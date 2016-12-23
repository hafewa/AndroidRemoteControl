//
// Created by prith on 12/7/2016.
//

#ifndef ANDROIDREMOTECONTROL_PERSISTENTDATAMANAGER_H
#define ANDROIDREMOTECONTROL_PERSISTENTDATAMANAGER_H


#include <string>
#include <unordered_map>
#include <unordered_set>

class Saveable;
class PersistentDataManager {

public:
    static PersistentDataManager& getInstance();
    void setDataFile(std::string& path);

    bool LoadPersistentData();
    bool SavePersistentData();

    const std::string& GetData(const std::string& key);

    void RegisterSaveable(Saveable* saveable);
    void UnregisterSaveable(Saveable* saveable);

private:
    PersistentDataManager();
    std::string mDataFilePath;
    std::unordered_map<std::string, std::string> mDataMap;

    std::unordered_set<Saveable*> mSaveables;
};


#endif //ANDROIDREMOTECONTROL_PERSISTENTDATAMANAGER_H
