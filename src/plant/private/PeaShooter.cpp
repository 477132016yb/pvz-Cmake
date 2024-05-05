//
// Created by yb on 2024/4/30.
//

#include "../public/PeaShooter.h"
PeaShooter::PeaShooter() {
    PeaShooter::m_cost=100;
    PeaShooter::m_type=plantType::PeaShooter;
    Atlas::SP atlas = std::make_shared<Atlas>(Singleton<res>::instanceSP()->atls_plants[int(m_type)]);
    this->m_action->setAtlas(atlas);
    this->m_action->setLoop(true);
    this->m_action->setInterval(75);
}
