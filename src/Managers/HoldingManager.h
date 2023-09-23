#ifndef MACTANGLE_HOLDINGMANAGER_H
#define MACTANGLE_HOLDINGMANAGER_H


#include <vector>
#include <memory>
#include "../BaseClasses/PositionableEntity.h"

class HoldingManager {
    std::vector<PositionableEntity *> m_toPut;
    bool m_isBusy;

    bool place();

public:
    bool addToQueue(PositionableEntity *entity, bool addIfBusy = false);

    bool getIsBusy();


    void manageCurrentEntity();
};


#endif //MACTANGLE_HOLDINGMANAGER_H
