//
// Created by prith on 12/7/2016.
//

#include "PersistentDataManager.h"
#include <fstream>
#include "Saveable.h"

using namespace std;

PersistentDataManager& PersistentDataManager::getInstance() {
    static PersistentDataManager dataMgr;

    return dataMgr;
}

PersistentDataManager::PersistentDataManager() : mDataFilePath(""){

}

void PersistentDataManager::setDataFile(std::string &path) {

    mDataFilePath= path;
}

bool PersistentDataManager::LoadPersistentData()
{
    // if there is no save file then this must be the first run!
    ifstream dataFile(mDataFilePath.c_str(), std::ifstream::in);
    if (dataFile.is_open())
    {
        string line;

        while(std::getline(dataFile, line))
        {
            std::string::size_type delimLoc = line.find("=");
            if (delimLoc != string::npos)
            {
                mDataMap[line.substr(0, delimLoc)] = line.substr(delimLoc + 1);
            }
            else
            {
                return  false;
            }
        }
        return true;
    }
    return false;
}

bool PersistentDataManager::SavePersistentData()
{
    ofstream dataFile(mDataFilePath.c_str());
    if(dataFile.is_open()) {
        for (Saveable *saveable : mSaveables) {
            saveable->Save(&dataFile);
        }
        return true;
    }
    return false;
}

const std::string& PersistentDataManager::GetData(const std::string &key)
{
    std::unordered_map<std::string, std::string>::iterator it = mDataMap.find(key);
    std::string result = "";

    if (it != mDataMap.end())
    {
        result = it->second;
    }

    return std::move(result);
}

void PersistentDataManager::RegisterSaveable(Saveable *saveable)
{
    if(saveable) {
        mSaveables.insert(saveable);
    }
}

void PersistentDataManager::UnregisterSaveable(Saveable *saveable)
{
    if(saveable)
    {
        mSaveables.erase(saveable);
    }
}