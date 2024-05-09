//
// Created by yb on 2024/4/30.
//

#include "GameScene.h"
void GameScene::on_draw() {
    m_objManager->draw();
}

void GameScene::on_enter() {
    LOG("进入游戏内场景");
}

void GameScene::on_update(int delta) {
    m_objManager->update(delta);
}

void GameScene::on_input(const ExMessage &msg) {
    m_objManager->input(msg);
}

void GameScene::on_exit() {
    LOG("游戏局内退出");
}

GameScene::GameScene() {
    m_objManager=Singleton<ObjManager>::instanceSP();
}

