//
// Created by yb on 2024/4/30.
//

#ifndef PVZ_PEASHOOTER_H
#define PVZ_PEASHOOTER_H
#include "plant.h"
class PeaShooter :public plant{
public:
    PeaShooter();
private:
    static plantType s_type;
    static int s_cost;
};

#endif //PVZ_PEASHOOTER_H
