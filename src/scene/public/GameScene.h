//
// Created by yb on 2024/4/30.
//

#ifndef PVZ_GAMESCENE_H
#define PVZ_GAMESCENE_H
#include <time.h>
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"
#include "SunShine.h"

class GameScene :public Scene{
public:
    GameScene();
    ~GameScene()=default;
public:
    void on_enter() override;
    void on_update(int delta) override;
    void on_draw() override;
    void on_input(const ExMessage& msg) override;
    void on_exit() override;
public:
    void creatObject(int delta);
    void creatSunShine(int delta);//´´½¨Ñô¹â
private:
    std::vector<std::vector<Object*>>m_plantMap;
    std::vector<SunShine*>m_sunShinePool;

    std::vector<IMAGE*>m_cardVault;
    IMAGE *m_bg;
    IMAGE *m_cardBar;
    IMAGE *m_cardMask;
};

#endif //PVZ_GAMESCENE_H
