#include "Saveable.h"


Saveable::Saveable()
{
    PersistentDataManager::getInstance().RegisterSaveable(this);
}
Saveable::~Saveable()
{
    PersistentDataManager::getInstance().UnregisterSaveable(this);
}
