//
// Created by yb on 2024/5/13.
//

#include "Chomper.h"
plant::plantType Chomper::s_type=plantType::Chomper;
Chomper::Chomper() {
    this->m_dy-=25;
    this->m_damage=500;
    this->setStatus(ChomperStatus::Normal);
    this->m_action->setLoop(true);
    this->m_action->setInterval(75);

    this->m_timer.setWaitTime(15000);
    this->m_timer.setOneTrigger(true);
    this->m_timer.setCallback([this](){
        setStatus(ChomperStatus::Normal);
    });
}

plant::plantType Chomper::getType() {
    return s_type;
}

void Chomper::setStatus(Chomper::ChomperStatus status) {
    m_status = status;
    Atlas ::SP atlas;
    switch (status) {
        case ChomperStatus::Normal:
            atlas=std::make_shared<Atlas>(Singleton<res>::instanceSP()->atls_plants[int(s_type)]);
            break;
        case ChomperStatus::Attack:
            atlas=std::make_shared<Atlas>(Singleton<res>::instanceSP()->atl_ChomperAttack);
            m_action->setLoop(false);
            m_action->setCallback([this](){
                setStatus(ChomperStatus::Digestion);
            });
            break;
        case ChomperStatus::Digestion:
            atlas=std::make_shared<Atlas>(Singleton<res>::instanceSP()->atl_ChomperDigestion);
            m_action->setLoop(true);
            this->m_timer.restart();
            break;
    }
    this->m_action->setAtlas(atlas);
}

void Chomper::collide(Object *obj) {
    if(!obj->m_isCollide){return;}
    if(yb::checkHitX(obj->m_x,m_x-50,150)&&m_status==ChomperStatus::Normal){
        setStatus(ChomperStatus::Attack);
        if(m_damage>=obj->m_blood){
            obj->m_used=false;
        }
        else{
            obj->m_blood-=20;
        }
    }
}

void Chomper::skills(int delta) {
    if(m_status==ChomperStatus::Digestion){
        m_timer.update(delta);
    }
}
