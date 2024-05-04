//
// Created by yb on 2024/4/30.
//

#include "../public/GameScene.h"
#include "PeaShooter.h"
REGISTER_CLASS(PeaShooter);
extern std::vector<const char*>plantNameList;
void GameScene::on_draw() {
    for(auto&a:m_plantMap){
        for(auto&b:a){
            if(b){
                b->draw();
            }
        }
    }
}

void GameScene::on_enter() {
    ClassFactory* factory = Singleton<ClassFactory>::instance();
    Object*a=(factory->create_class(plantNameList[0]));
    m_plantMap[0].push_back(a);
    LOG("进入游戏内场景");
}

void GameScene::on_update(int delta) {
    for(auto&a:m_plantMap){
        for(auto&b:a){
            if(b){
                b->update(delta);
            }
        }
    }
}

void GameScene::on_input(const ExMessage &msg) {
    if(msg.message==WM_KEYDOWN){
        Singleton<SceneManager>::instance()->switchTo(SceneManager::SceneType::Menu);
    }
}

void GameScene::on_exit() {
    LOG("游戏局内退出");
}

GameScene::GameScene() {
    m_plantMap = std::vector<std::vector<Object*>>(5, std::vector<Object*>(10,NULL));
}

