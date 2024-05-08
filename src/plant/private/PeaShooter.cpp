//
// Created by yb on 2024/4/30.
//

#include "../public/PeaShooter.h"
plant::plantType PeaShooter::s_type=plantType::PeaShooter;
PeaShooter::PeaShooter() {
    Atlas ::SP atlas=std::make_shared<Atlas>(Singleton<res>::instanceSP()->atls_plants[int(s_type)]);
    this->m_action->setAtlas(atlas);
    this->m_action->setLoop(true);
    this->m_action->setInterval(75);
}

plant::plantType PeaShooter::getType() {
    return s_type;
}
