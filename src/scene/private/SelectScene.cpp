//
// Created by yb on 2024/5/2.
//

#include "SelectScene.h"
extern std::vector<int> g_selectNum;
SelectScene::SelectScene() {
    res::SP r=Singleton<res>::instanceSP();
    m_camera=Singleton<Camera>::instanceSP();
    m_fightButton=std::make_shared<Button>();
    m_bg=&r->img_bg;
    m_PanelBackGround=&r->img_PanelBackGround;
    m_cardBar=&r->img_selectBar;
    m_cardVault.resize(r->imgs_selectCard.size());
    for(int i=0;i<m_cardVault.size();i++){
        m_cardVault[i]=&r->imgs_selectCard[i];
    }
    m_cardWidth=50;
    m_cardHeight=72;
    m_isCardSelect.resize(m_cardVault.size());
    m_cardMask=&r->img_selectCardMask;

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
        int objY=m_cardBar->getheight();
        putimage(0,0,m_cardBar);
        putimage(0,objY,m_PanelBackGround);
        m_fightButton->draw();

        for(int i=0;i<m_cardVault.size();i++){
            int row=i/8,col=i%8;
            int x=25+col*(m_cardWidth+2);
            int y=objY+40+row*(m_cardHeight+1);
            putimage(x,y,m_cardVault[i]);
            if(m_isCardSelect[i]){
                putimagePNG(x,y,m_cardMask);
            }
        }

        for(int i=0;i<g_selectNum.size();i++){
            if(g_selectNum[i]==-1){break;}
            int num=g_selectNum[i];
            int x=78+i*(m_cardWidth+5);
            int y=5;
            putimage(x,y,m_cardVault[num]);
        }
    }
}

void SelectScene::on_input(const ExMessage &msg) {
    m_fightButton->processEvent(msg);
    static int num=-1,idx=-1;
    switch (msg.message) {
        case WM_LBUTTONDOWN:
            if (msg.x > 78 && msg.x < 78 + 55 * (g_selectNum.size()) && msg.y < 5+m_cardHeight && msg.y>5) {
                idx = (msg.x - 78) / 55;
            }
            else if (msg.x > 25 && msg.x < 24 + 52 * 8 && msg.y < 76*2+131 && msg.y>131) {
                num = (msg.x - 25) / 52 + ((msg.y - 131) / 76)*8;
            }
            break;
        case WM_LBUTTONUP:
            if (idx != -1) {
                if(g_selectNum[idx]==-1){
                    break;
                }
                m_isCardSelect[g_selectNum[idx]]=false;
                for(int i=idx;i<g_selectNum.size()-1;i++){
                    g_selectNum[i]=g_selectNum[i+1];
                }
                g_selectNum.back()=-1;
                idx = -1;
            }
            if (num != -1) {
                if(m_isCardSelect[num]){
                    break;
                }
                for (int i = 0; i < g_selectNum.size();i++) {
                    if(g_selectNum[i]==-1){
                        g_selectNum[i]=num;
                        m_isCardSelect[num]=true;
                        break;
                    }
                }
                num = -1;
            }
            break;
        default:
            break;
    }
}

void SelectScene::on_exit() {
    m_camera->reset();
    LOG("离开选择场景");
}
