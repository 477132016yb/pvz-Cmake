//
// Created by yb on 2024/4/28.
//

#ifndef PVZ_PLANT_H
#define PVZ_PLANT_H

#include "ClassFactory.h"
#include "Animation.h"
#include "res.h"

class plant :public Object {
public:
    enum class plantType{
        PeaShooter,
        SunFlower,
        SnowPea,
        None
    };
public:
    plant();
    ~plant() override =default;
    void update(int delta) override;
    void draw() override;
    virtual void skills(int delta){};
public:
    virtual plantType getType()=0;
protected:
    Animation::SP m_action;
    int m_skillTime;
};

#endif //PVZ_PLANT_H
