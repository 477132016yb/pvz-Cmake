//
// Created by yb on 2024/4/30.
//

#ifndef PVZ_SUNFLOWER_H
#define PVZ_SUNFLOWER_H

#include "plant.h"
class SunFlower: public plant{
public:
    SunFlower();
public:
    plantType getType() override;
private:
    static plantType s_type;
};


#endif //PVZ_SUNFLOWER_H
