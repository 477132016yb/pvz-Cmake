//
// Created by yb on 2024/5/10.
//

#include"Zombie.h"

Zombie::Zombie() {
    m_action = std::make_shared<Animation>();
    m_atls.resize(4);
    m_speed=-2;
    m_timer=0;
    m_x = 850+ rand() % 100;
    m_row = rand() % 5;
    m_y = 30 + 100 * m_row;
}

void Zombie::draw() {
    m_action->draw(m_x,m_y);
}

void Zombie::update(int delta) {
    m_action->update(delta);
    m_timer+=delta;
    if(m_timer<60){return;}
    m_col = ((m_x - 144) / 81) + 1;
    m_timer=0;
    switch (m_status) {
        case ZombieStatus::Stand:
            break;
        case ZombieStatus::Walking:
            m_x+=m_speed;
            if(m_x<0){
                m_used=false;
            }
            break;
        case ZombieStatus::Attack:
            break;
        case ZombieStatus::FallDown:
            break;
        case ZombieStatus::Ashes:
            break;
        default:
            break;
    }
}

bool Zombie::collide(Object *obj) {
    return Object::collide(obj);
}
