//
// Created by yb on 2024/5/10.
//

#ifndef PVZ_BULLET_H
#define PVZ_BULLET_H
#include "Object.h"
#include "const.h"
#include "Animation.h"
#include <functional>

class Bullet : public Object{
public:
    ~Bullet() override =default;
    Bullet();
public:
    enum class BulletType{
        Normal,Cool,Fire,Blast
    };
public:
    void update(int delta) override;
    void draw() override;
    bool collide(Object*obj) override;
    void setImage(IMAGE*img,std::vector<IMAGE>&vec);
public:
    int m_speed;
    int m_row;
    int m_damage;
    BulletType m_type;
protected:
    IMAGE*m_img;
    std::vector<IMAGE*>m_imgs;
    int m_timer,m_idx;
};


#endif //PVZ_BULLET_H
