//
// Created by yb on 2024/5/10.
//

#ifndef PVZ_ZOMBIE_H
#define PVZ_ZOMBIE_H

#include "Object.h"
#include "Animation.h"
#include "res.h"
class Zombie :public Object{
public:
    Zombie();
    ~Zombie() override = default;
public:
    enum class ZombieType{
        NormalZombie,
        RoadBlockZombie
    };
    enum class ZombieStatus{
        Stand,
        Walking,
        Attack,
        FallDown,
        Ashes,
        None
    };
public:
    void update(int delta) override;
    void draw() override;
    bool collide(Object*obj) override;
public:
    int m_row{},m_col{};
protected:
    int m_speed;
    int m_timer;
    ZombieStatus m_status;
    Animation::SP m_action;
    std::vector<Atlas::SP> m_atls;
};


#endif //PVZ_ZOMBIE_H
