//
// Created by yb on 2024/5/10.
//

#include"Zombie.h"
int Zombie::s_creatTime=80000;
Zombie::Zombie() {
    m_action = std::make_shared<Animation>();
    m_atls.resize(4);
    m_speed=2;
    m_timer=0;
    m_x = 850+ rand() % 100;
    m_row = rand() % 5;
    m_y = 30 + 100 * m_row;
    m_damage=20;
}

void Zombie::draw() {
    m_action->draw(m_x,m_y);
}

void Zombie::update(int delta) {
    m_action->update(delta);
    m_timer+=delta;
    if(m_timer<120){return;}
    m_timer=0;
    m_col = ((m_x - 144) / 81) + 1;
    if(m_blood<0&&m_blood>-30&&m_status!=ZombieStatus::FallDown){
        setStatus(ZombieStatus::FallDown);
        m_action->reset();
        m_action->setLoop(false);
        m_action->setCallback([this](){
            m_used=false;
        });
    }
    switch (m_status) {
        case ZombieStatus::Stand:
            break;
        case ZombieStatus::Walking:
            m_x-=m_speed;
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

void Zombie::collide(Object *obj) {
    if(!obj){return;}
    static int count=0;
    if(m_status!=ZombieStatus::Attack&&m_status!=ZombieStatus::Walking){return;}
    if(yb::checkHitX(m_x,obj->m_x-50,30)){
        if(m_status==ZombieStatus::Walking){
            setStatus(ZombieStatus::Attack);
        }
        count++;
        if(count>30){
            count=0;
            obj->m_blood-=m_damage;
        }
        if(!obj->m_used){
            setStatus(ZombieStatus::Walking);
        }
    }
}

void Zombie::setStatus(Zombie::ZombieStatus status) {
    m_status=status;
    m_action->setAtlas(m_atls[int(m_status)]);
}
