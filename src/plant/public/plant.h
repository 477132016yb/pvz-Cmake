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
        None
    };
public:
    plant();
    ~plant()=default;
    void update(int delta) override;
    void draw() override;
public:
    int m_row{},m_col{};
    int m_blood=100;
    Animation::SP m_action;
public:
    static plantType m_type;
    static int m_cost;
protected:
    static int m_dy;
    static Atlas::SP m_atls;
};

#endif //PVZ_PLANT_H
