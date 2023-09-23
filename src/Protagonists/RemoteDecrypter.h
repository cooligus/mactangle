//
// Created by pewie on 21.09.2023.
//

#ifndef MACTANGLE_REMOTEDECRYPTER_H
#define MACTANGLE_REMOTEDECRYPTER_H


#include "../BaseClasses/PositionableEntity.h"

class RemoteDecrypter : public PositionableEntity {
public:
    RemoteDecrypter();

    void makeReadyToGo() override;
};


#endif //MACTANGLE_REMOTEDECRYPTER_H
