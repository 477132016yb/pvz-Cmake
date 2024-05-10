//
// Created by yb on 2024/5/10.
//

#include "Bullet.h"

bool Bullet::collide(Object *obj) {
    return yb::checkHit(m_x,m_y,obj->m_x+80,obj->m_y,30,100);
}

void Bullet::draw() {
    if (m_type!=BulletType::Blast){
        putimagePNG(m_x,m_y,m_img);
    }
    else{
        putimagePNG(m_x,m_y,m_imgs[m_idx]);
    }
}

void Bullet::update(int delta) {
    m_timer+=delta;
    if(m_timer<30){return;}
    m_timer=0;
    if (m_x >= WIN_WIDTH) {
        m_used=false;
    }
    if (m_type!=BulletType::Blast) {
        m_x += m_speed;
    }
    else{
        m_idx++;
        if (m_idx == 4) {
            m_used = false;
        }
    }
}

Bullet::Bullet() {
    m_idx=0;
    m_timer=0;
    m_speed=10;
    m_damage=13;
    m_type=BulletType::Normal;
}

void Bullet::setImage(IMAGE *img, std::vector<IMAGE> &vec) {
    m_img=img;
    m_imgs.resize(vec.size());
    for(int i=0;i<m_imgs.size();i++){
        m_imgs[i]=&vec[i];
    }
}
