//
// Created by yb on 2024/5/7.
//

#include "../public/ObjManager.h"
#include "PeaShooter.h"
#include "SunFlower.h"
#include "SunShine.h"
REGISTER_CLASS(PeaShooter);
REGISTER_CLASS(SunShine);
REGISTER_CLASS(SunFlower);
extern std::vector<const char*>plantNameList;
extern std::vector<int> g_selectNum;
ObjManager::ObjManager() {
    m_sun=50;
    m_cur= nullptr;
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

void ObjManager::update(int delta) {
    creatObject(delta);
    updateMemory();
    for(auto&a:m_plantMap){
        yb::updateVector(a,delta);
    }
    yb::updateVector(m_sunShinePool,delta);
}

void ObjManager::draw() {
    putimage(-112,0,m_bg);
    putimage(250 - 112,0,m_cardBar);

    char sun[8];
    sprintf_s(sun, sizeof(sun), "%d", m_sun);
    outtextxy(278-112, 69, sun);

    for(int i=0;i<g_selectNum.size();i++){
        if(g_selectNum[i]==-1){break;}
        int num=g_selectNum[i];
        int x=339 - 112+i*(m_cardVault[num]->getwidth()+5);
        int y=8;
        putimage(x,y,m_cardVault[num]);
    }
    for(auto&a:m_plantMap){
        yb::drawVector(a);
    }
    if(m_cur){
        m_cur->draw();
    }
    yb::drawVector(m_sunShinePool);
}

void ObjManager::input(const ExMessage &msg) {
    static int idx = 0;
    ClassFactory* factory = Singleton<ClassFactory>::instance();
    switch (msg.message) {
        case WM_LBUTTONDOWN:
            if (!m_cur&&msg.x > 227 && msg.x < 227 + 64 * g_selectNum.size() && msg.y < 96 && msg.y>8) {
                idx = (msg.x - (227)) / 64;
                m_cur = factory->create_class(plantNameList[g_selectNum[idx]]);
            }
            else{
                checkSunShine(msg);
            };
            break;
        case WM_MOUSEMOVE:
            if(m_cur){
                m_cur->m_x=msg.x-20;
                m_cur->m_y=msg.y-20;
            }
            break;
        case WM_LBUTTONUP:
        {
            int x = msg.x;
            int y = msg.y;
            if (x > 144 && y > 77 && y < 591) {
                int row = (y - 77) / 102;
                int col = (x - 144) / 81;
                if (m_cur&&(!m_plantMap[row][col]) ) {
                    m_cur->m_y = 77 + row * 102;
                    m_cur->m_x = 144 + col * 81;
                    m_plantMap[row][col] = m_cur;
                }
            }
            m_cur= nullptr;
        }
            break;
        default:
            break;
    }
}

void ObjManager::checkSunShine(const ExMessage &msg) {
    for(auto&a:m_sunShinePool){
        if(a){
            if(yb::checkHit(msg.x,msg.y,a->m_x+5,a->m_y+5,60,60)){
                SunShine*b = dynamic_cast<SunShine*>(a);
                if(b){
                    b->m_status = SunShine::SunStatus::SUNSHINE_COLLECT;
                    b->m_t = 0;
                    b->p1.x = b->m_curp.x;
                    b->p1.y = b->m_curp.y;
                    b->p4 = vector2(150, 0);
                    float distance = (b->p1 - b->p4).dis();
                    float off = 50;
                    b->m_speed = 1.0/(distance/off);
                    m_sun+=25;
                }
            }
        }
    }
}

void ObjManager::updateMemory() {
    yb::clearVector(m_sunShinePool);
}

void ObjManager::creatObject(int delta) {
    creatSunShine(delta);
}

void ObjManager::creatSunShine(int delta) {
    static int count = 0;
    count+=delta;
    static int fre = 10;
    if (count > fre) {
        count = 0;
        fre = SunShine::s_creatTime + rand() % 2000;
        ClassFactory* factory = Singleton<ClassFactory>::instance();
        SunShine*a = dynamic_cast<SunShine*>(factory->create_class("SunShine"));
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
