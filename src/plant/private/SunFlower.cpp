//
// Created by yb on 2024/4/30.
//

#include "SunFlower.h"

SunFlower::SunFlower() {
    SunFlower::m_cost=m_cost=50;
    SunFlower::m_type=plantType::SunFlower;
    Atlas::SP atlas= std::make_shared<Atlas>(Singleton<res>::instanceSP()->atls_plants[int(m_type)]);
    this->m_action->setAtlas(atlas);
    this->m_action->setLoop(true);
}
