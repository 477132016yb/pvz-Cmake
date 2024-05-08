//
// Created by yb on 2024/4/30.
//

#include "SunFlower.h"
plant::plantType SunFlower::s_type=plantType::SunFlower;

SunFlower::SunFlower() {
    Atlas ::SP atlas=std::make_shared<Atlas>(Singleton<res>::instanceSP()->atls_plants[int(s_type)]);
    this->m_action->setAtlas(atlas);
    this->m_action->setLoop(true);
    this->m_action->setInterval(75);
}

plant::plantType SunFlower::getType() {
    return s_type;
}
