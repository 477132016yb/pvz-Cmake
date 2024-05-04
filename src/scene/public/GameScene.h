//
// Created by yb on 2024/4/30.
//

#ifndef PVZ_GAMESCENE_H
#define PVZ_GAMESCENE_H
#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"

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
private:
    std::vector<std::vector<Object*>>m_plantMap;
};

#endif //PVZ_GAMESCENE_H
