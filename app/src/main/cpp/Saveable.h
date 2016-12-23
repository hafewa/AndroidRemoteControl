//
// Created by prith on 12/22/2016.
//

#ifndef ANDROIDREMOTECONTROL_SAVEABLE_H
#define ANDROIDREMOTECONTROL_SAVEABLE_H

#include <fstream>
#include "PersistentDataManager.h"

class Saveable
{
public:
    Saveable();
    ~Saveable();
    virtual void Save(std::ofstream* saveFile) = 0;
};


#endif //ANDROIDREMOTECONTROL_SAVEABLE_H
