//
// Created by yb on 2024/5/2.
//

#include "../public/SelectScene.h"

SelectScene::SelectScene() {
    res::SP r=Singleton<res>::instanceSP();
    m_camera=Singleton<Camera>::instanceSP();
    m_fightButton=std::make_shared<Button>();
    m_bg=&r->img_bg;
    m_PanelBackGround=&r->img_PanelBackGround;
    m_ChooserBackground=&r->img_ChooserBackground;
    m_cardVault.resize(r->imgs_card.size());
    for(int i=0;i<m_cardVault.size();i++){
        m_cardVault[i]=&r->imgs_card[i];
    }
    m_isCardSelect.resize(m_cardVault.size());
    m_cardMask=&r->img_cardMask;

    m_fightButton->setRect({155,545,150+150,550+40});
    m_fightButton->setImage(r->imgs_fightButton);
    m_fightButton->setCallback([this](){
//        m_camera->reSetSpeed();
//        m_camera->timerReSet();
        Singleton<SceneManager>::instance()->switchTo(SceneManager::SceneType::Game);
    });
}

void SelectScene::on_enter() {
    LOG("进入选择场景");
    m_fightButton->reSet();
}

void SelectScene::on_update(int delta) {
    m_camera->update(delta);
}

void SelectScene::on_draw() {
    putimage(0-m_camera->getPosition().x,0-m_camera->getPosition().y,m_bg);
    if(m_camera->isTrigger()){
        int objY=m_ChooserBackground->getheight();
        putimage(0,0,m_ChooserBackground);
        putimage(0,objY,m_PanelBackGround);
        m_fightButton->draw();

        for(int i=0;i<m_cardVault.size();i++){
            int row=i/8,col=i%8;
            int width=m_cardVault[i]->getwidth();
            int height=m_cardVault[i]->getheight();
            int x=25+col*(width+2);
            int y=objY+40+row*(height+1);
            putimage(x,y,m_cardVault[i]);
            if(!m_isCardSelect[i]){
                putimagePNG(x,y,m_cardMask);
            }
        }
    }
}

void SelectScene::on_input(const ExMessage &msg) {
    m_fightButton->processEvent(msg);
}

void SelectScene::on_exit() {
    m_camera->reset();
    LOG("离开选择场景");
}
