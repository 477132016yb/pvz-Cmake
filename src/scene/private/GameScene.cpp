//
// Created by yb on 2024/4/30.
//

#include "../public/GameScene.h"
#include "PeaShooter.h"
REGISTER_CLASS(PeaShooter);
extern std::vector<const char*>plantNameList;
extern std::vector<int> g_selectNum;
void GameScene::on_draw() {
    putimage(-112,0,m_bg);
    putimage(250 - 112,0,m_cardBar);
    for(int i=0;i<g_selectNum.size();i++){
        if(g_selectNum[i]==-1){break;}
        int num=g_selectNum[i];
        int x=339 - 112+i*(m_cardVault[num]->getwidth()+5);
        int y=8;
        putimage(x,y,m_cardVault[num]);
    }
    for(auto&a:m_plantMap){
        for(auto&b:a){
            if(b){
//                b->draw();
            }
        }
    }
    for(auto&a:m_sunShinePool){
        if(a){
            a->draw();
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
    creatObject(delta);
    for(auto&a:m_plantMap){
        for(auto&b:a){
            if(b){
                b->update(delta);
            }
        }
    }
    for(auto&a:m_sunShinePool){
        if(a){
            a->update(delta);
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
    srand(time(nullptr));
    res::SP r=Singleton<res>::instanceSP();
    m_bg=&r->img_bg;
    m_cardBar=&r->img_gameBar;
    m_cardVault.resize(r->imgs_gameCard.size());
    for(int i=0;i<m_cardVault.size();i++){
        m_cardVault[i]=&r->imgs_gameCard[i];
    }
    m_cardMask=&r->img_gameCardMask;

    m_plantMap = std::vector<std::vector<Object*>>(5, std::vector<Object*>(10,nullptr));
}

void GameScene::creatSunShine(int delta) {
    static int count = 0;
    count+=delta;
    static int fre = 10;
    if (count > fre) {
        count = 0;
        fre = 5000 + rand() % 2000;
//        int i = 0;
//        while (i<m_sunShinePool.size()&&m_sunShinePool[i]->m_used) { i++; }
//        if (i >= m_sunShinePool.size()) { return; }
//        SunShine::SP a = m_sunShinePool[i];

        SunShine* a=new SunShine();
        a->m_used = true;
        a->m_status = SunShine::SunStatus::SUNSHINE_DOWN;
        a->p1 = vector2(260 + rand() % 540, 60);
        a->p4 = vector2(a->p1.x, 230 + (rand() % 4) * 90);
        a->m_t=0;
        float distance = (a->p1 - a->p4).dis();
        float off = 1;
        a->m_speed = 1.0 / (distance / off);
        m_sunShinePool.push_back(a);
    }
}

void GameScene::creatObject(int delta) {
    creatSunShine(delta);
}

