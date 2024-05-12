//
// Created by yb on 2024/5/12.
//
#include "plant.h"
#ifndef PVZ_POTATOMINE_H
#define PVZ_POTATOMINE_H

class PotatoMine :public plant{
public:
    PotatoMine();
public:
    plantType getType() override;
    void skills(int delta)override;
private:
    static plantType s_type;
};


#endif //PVZ_POTATOMINE_H
