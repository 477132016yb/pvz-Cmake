//
// Created by yb on 2024/4/30.
//

#ifndef PVZ_SUNFLOWER_H
#define PVZ_SUNFLOWER_H

#include "plant.h"
class SunFlower: public plant{
public:
    SunFlower();
private:
    static plantType s_type;
    static int s_cost;
};


#endif //PVZ_SUNFLOWER_H
