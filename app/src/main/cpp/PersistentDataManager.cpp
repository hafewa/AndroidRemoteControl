//
// Created by prith on 12/7/2016.
//

#include "PersistentDataManager.h"
#include <fstream>

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

void PersistentDataManager::LoadPersistentData()
{
    // if there is no save file then this must be the first run!
    ifstream file(mDataFilePath);
    if (file.is_open())
    {
        string line;
        std::getline(file, line);
    }
    else
    {
        //todo
    }
}

void PersistentDataManager::SavePersistentData()
{
    ofstream file(mDataFilePath);
    if (file.is_open())
    {
        char line[100];
        file << line;
    }
    file.close();
}