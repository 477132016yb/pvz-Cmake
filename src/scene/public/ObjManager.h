//
// Created by yb on 2024/5/7.
//

#ifndef PVZ_OBJMANAGER_H
#define PVZ_OBJMANAGER_H

#include "Object.h"
#include <ctime>
#include "SceneManager.h"
class ObjManager {
public:
    using SP=std::shared_ptr<ObjManager>;
    ObjManager();
    ~ObjManager()=default;
public:
    void update(int delta);
    void draw();
    void input(const ExMessage& msg);
private:
    void checkSunShine(const ExMessage& msg);
    void updateMemory();
    void creatObject(int delta);
    void creatSunShine(int delta);//´´½¨Ñô¹â
private:
    int m_sun;
    Object*m_cur;
    std::vector<std::vector<Object*>>m_plantMap;
    std::vector<Object*>m_sunShinePool;

    std::vector<IMAGE*>m_cardVault;
    IMAGE *m_bg;
    IMAGE *m_cardBar;
    IMAGE *m_cardMask;
};


#endif //PVZ_OBJMANAGER_H
