//
// Created by yb on 2024/4/30.
//

#include "../public/PeaShooter.h"
PeaShooter::PeaShooter() {
    Atlas ::SP atlas=std::make_shared<Atlas>(Singleton<res>::instanceSP()->atls_plants[int(s_type)]);
    this->m_action->setAtlas(atlas);
    this->m_action->setLoop(true);
    this->m_action->setInterval(75);
}

void PeaShooter::init() {
    s_cost=100;
    s_type=plantType::PeaShooter;
}
