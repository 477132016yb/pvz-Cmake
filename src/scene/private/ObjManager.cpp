//
// Created by yb on 2024/5/7.
//

#include "ObjManager.h"
#include "PeaShooter.h"
#include "SunFlower.h"
#include "SunShine.h"
REGISTER_CLASS(StaticObj);
REGISTER_CLASS(PeaShooter);
REGISTER_CLASS(SunFlower);
extern std::vector<int> g_selectNum;
ClassFactory* g_factory=Singleton<ClassFactory>::instance();
ObjManager::ObjManager() {
    m_sun= 50;
    m_cur= nullptr;
    m_isMove=false;
    srand(time(nullptr));
    res::SP r=Singleton<res>::instanceSP();
    int n=r->imgs_gameCard.size();
    m_cardVault.resize(n);
    for(int i=0;i<n;i++){
        m_cardVault[i]=&r->imgs_gameCard[i];
    }

    m_vriPlantVec.resize(r->imgs_vriPlantVec.size());
    for(int i=0;i<m_vriPlantVec.size();i++){
        m_vriPlantVec[i]=&r->imgs_vriPlantVec[i];
    }

    m_bg=&r->img_bg;
    m_cardBar=&r->img_gameBar;
    m_cardMask=&r->img_gameCardMask;
    m_shovelSlot=&r->img_shovelSlot;

    m_cardCoolAtion.resize(g_selectNum.size());
    Atlas::SP atlas=std::make_shared<Atlas>(r->atl_cardCoolTime);
    for(int i=0;i<m_cardCoolAtion.size();i++){
        m_cardCoolAtion[i]=std::make_shared<Animation>();
        m_cardCoolAtion[i]->setAtlas(atlas);
        m_cardCoolAtion[i]->setInterval(yb::plantCoolTimeList[g_selectNum[i]]);
        m_cardCoolAtion[i]->setLoop(false);
    }

    m_shovelObj = dynamic_cast<StaticObj*>(g_factory->create_class("StaticObj"));
    m_virtualPlant = dynamic_cast<StaticObj*>(g_factory->create_class("StaticObj"));
    m_shovelObj->setImage(&r->img_shovel);
    m_shovelObj->m_x=760,m_shovelObj->m_y=-10;

    m_plantMap = std::vector<std::vector<Object*>>(5, std::vector<Object*>(10,nullptr));
}

void ObjManager::update(int delta) {
    creatObject(delta);
    updateMemory();
    for(auto&a:m_plantMap){
        yb::updateVector(a,delta);
    }
    yb::updateVector(m_sunShinePool,delta);
    yb::updateVector(m_bulletPool,delta);
    for(auto&a:m_cardCoolAtion){a->update(delta);}
}

void ObjManager::draw() {
    putimage(-112,0,m_bg);
    putimage(250 - 112,0,m_cardBar);
    putimagePNG(750,0,m_shovelSlot);
    m_shovelObj->draw();
    if(m_isMove){
        m_virtualPlant->draw();
    }

    char sun[8];
    sprintf_s(sun, sizeof(sun), "%d", m_sun);
    outtextxy(278-112, 69, sun);

    for(int i=0;i<g_selectNum.size();i++){
        if(g_selectNum[i]==-1){break;}
        int num=g_selectNum[i];
        int x=339 - 112+i*(m_cardVault[num]->getwidth()+5);
        int y=8;
        putimage(x,y,m_cardVault[num]);
        if(m_sun<yb::plantCostList[g_selectNum[i]]){
            putimagePNG(x,y,m_cardMask);
        }
        m_cardCoolAtion[i]->draw(x,y);
    }
    for(auto&a:m_plantMap){
        yb::drawVector(a);
    }
    if(m_cur){
        m_cur->draw();
    }
    yb::drawVector(m_sunShinePool);
    yb::drawVector(m_bulletPool);
}

void ObjManager::input(const ExMessage &msg) {
    switch (msg.message) {
        case WM_LBUTTONDOWN:
            processLeftButton(msg);
            m_isMove=false;
            break;
        case WM_MOUSEMOVE:
        {
            if(m_cur){
                m_cur->m_x=msg.x-20;
                m_cur->m_y=msg.y-20;
                if(m_cur->getName()!="StaticObj"){
                    m_isMove=true;
                }
            }
            int x = msg.x;
            int y = msg.y;
            if (x > 144 && y > 77 && y < 591) {
                int row = (y - 77) / 102;
                int col = (x - 144) / 81;
                m_virtualPlant->m_y = 77 + row * 102;
                m_virtualPlant->m_x = 144 + col * 81;
            }
        }
            break;
        case WM_RBUTTONDOWN:
            if(m_cur){
                m_cur = nullptr;
                m_virtualPlant= nullptr;
                m_shovelObj->m_x=760,m_shovelObj->m_y=-10;
            }
            break;
        case WM_LBUTTONUP:
            break;
        default:
            break;
    }
}

void ObjManager::checkSunShine(const ExMessage &msg) {
    for(auto&a:m_sunShinePool){
        if(!a){ continue;}
        if(yb::checkHit(msg.x,msg.y,a->m_x+5,a->m_y+5,60,60)){
            auto*b = dynamic_cast<SunShine*>(a);
            if(!b){ continue;}
            b->collect();
            m_sun+=25;
        }
    }
}

void ObjManager::updateMemory() {
    yb::clearVector(m_sunShinePool);
    yb::clearVector(m_bulletPool);
}

void ObjManager::creatObject(int delta) {
    creatSunShine(delta);
}

void ObjManager::creatSunShine(int delta) {
    static int count = 0;
    count += delta;
    static int fre = 10;
    if (count <=fre) {return;}
    count = 0;
    fre = SunShine::s_creatTime + rand() % 2000;

    SunShine*a =SunShine::creatSunShine();
    m_sunShinePool.push_back(a);
}

std::vector<Object *> &ObjManager::getSunShineVec() {
    return m_sunShinePool;
}

ObjManager::~ObjManager() {
    delete m_shovelObj;
    delete m_virtualPlant;
}

void ObjManager::processLeftButton(const ExMessage &msg) {
    static int idx = -1;
    if (!m_cur&&msg.x > 227 && msg.x < 227 + 64 * g_selectNum.size() && msg.y < 96 && msg.y>8) {
        idx = (msg.x - (227)) / 64;
        if(m_sun<yb::plantCostList[g_selectNum[idx]]||!m_cardCoolAtion[idx]->checkFinished()){ return;}
        m_cur = g_factory->create_class(yb::plantNameList[g_selectNum[idx]]);
        m_virtualPlant->setImage(m_vriPlantVec[g_selectNum[idx]]);
    }
    else if (msg.x>750&&msg.x<750+70&&msg.y<70&&msg.y>10) {
        m_cur=m_shovelObj;
    }
    else if(m_cur){
        int x = msg.x;
        int y = msg.y;
        if (x > 144 && y > 77 && y < 591) {
            int row = (y - 77) / 102;
            int col = (x - 144) / 81;
            if (m_cur&&(!m_plantMap[row][col])&&idx!=-1) {//植物种下
                m_cur->m_y = 77 + row * 102;
                m_cur->m_x = 144 + col * 81;
                auto a= dynamic_cast<plant*>(m_cur);
                a->m_row=row,a->m_col=col;
                m_plantMap[row][col] = a;
                m_sun-=yb::plantCostList[idx];
                m_cardCoolAtion[idx]->reset();
                m_cur= nullptr;
                idx=-1;
            }
            else if(m_cur&&m_plantMap[row][col]&&m_cur->getName()=="StaticObj"){//铲子按下
                delete m_plantMap[row][col];
                m_plantMap[row][col]= nullptr;
                m_cur = nullptr;
                m_shovelObj->m_x=760,m_shovelObj->m_y=-10;
            }
        }
    }
    else{
        checkSunShine(msg);
    };
}

std::vector<Object *> &ObjManager::getBulletVec() {
    return m_bulletPool;
}

