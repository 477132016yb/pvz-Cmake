//
// Created by yb on 2024/4/28.
//

#include "../public/plant.h"

plant::plantType plant::s_type=plantType::None;
int plant::s_cost=100;
int plant::s_dy=0;

void plant::draw() {
    m_action->draw(m_x-(int)m_CameraPos.x,m_y-(int)m_CameraPos.y);
}

void plant::update(int delta) {
    m_action->update(delta);
}

plant::plant() {
    m_action = std::make_shared<Animation>();
}
