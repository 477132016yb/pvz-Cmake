//
// Created by yb on 2024/4/30.
//

#include "SunFlower.h"

SunFlower::SunFlower() {
    SunFlower::m_cost=m_cost=50;
    SunFlower::m_type=plantType::SunFlower;
    SunFlower::m_atls= std::make_shared<Atlas>(Singleton<res>::instanceSP()->atl_plants[int(m_type)]);
    this->m_action->setAtlas(SunFlower::m_atls);
    this->m_action->setLoop(true);
}
