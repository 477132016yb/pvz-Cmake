//
// Created by yb on 2024/5/7.
//

#ifndef PVZ_OBJMANAGER_H
#define PVZ_OBJMANAGER_H

#include "Object.h"
#include <ctime>
#include "SceneManager.h"
#include "Animation.h"
#include "StaticObj.h"
class ObjManager {
public:
    using SP=std::shared_ptr<ObjManager>;
    ObjManager();
    ~ObjManager();
    std::vector<Object*>& getSunShineVec();
    std::vector<Object*>& getBulletVec();
public:
    void update(int delta);
    void draw();
    void input(const ExMessage& msg);
private:
    void processLeftButton(const ExMessage& msg);
    void checkSunShine(const ExMessage& msg);
    void updateMemory();
    void creatObject(int delta);
    void creatSunShine(int delta);//创建阳光
    void creatZombie(int delta);//创建僵尸
private:
    int m_sun;
    Object*m_cur;
    StaticObj *m_shovelObj;
    std::vector<std::vector<Object*>>m_plantMap;
    std::vector<std::vector<Object*>>m_zombiePool;
    std::vector<Object*>m_sunShinePool;
    std::vector<Object*>m_bulletPool;

    std::vector<Animation::SP>m_cardCoolAtion;
    std::vector<IMAGE*>m_cardVault;
    std::vector<IMAGE*>m_vriPlantVec;
    IMAGE *m_bg;
    IMAGE *m_cardBar;
    IMAGE *m_cardMask;
    IMAGE *m_shovelSlot;
    StaticObj *m_virtualPlant;
    bool m_isMove;//鼠标是否在移动
};


#endif //PVZ_OBJMANAGER_H
