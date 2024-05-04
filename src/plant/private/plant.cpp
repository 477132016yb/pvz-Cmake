//
// Created by yb on 2024/4/28.
//

#include "../public/plant.h"

plant::plantType plant::m_type=plantType::None;
int plant::m_cost=100;
int plant::m_dy=0;
Atlas::SP plant::m_atls= nullptr;

void plant::draw() {
    m_action->draw(m_x-(int)m_CameraPos.x,m_y-(int)m_CameraPos.y);
}

void plant::update(int delta) {
    m_action->update(delta);
}

plant::plant() {
    m_action = std::make_shared<Animation>();
}
