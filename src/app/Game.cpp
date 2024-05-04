//
// Created by yb on 2024/4/29.
//

#include "Game.h"
Scene* g_gameSence=Singleton<GameScene>::instance();
Scene* g_menuSence=Singleton<MenuScene>::instance();
Scene* g_selectSence=Singleton<SelectScene>::instance();
void Game::play() {
    init();
    ExMessage msg;
    BeginBatchDraw();
    m_sceneManager->setCurrentState(g_menuSence);
    while (true) {
        DWORD frame_start_time=GetTickCount();
        while(peekmessage(&msg)){
            m_sceneManager->input(msg);
        }
        static DWORD last_tick_time=GetTickCount();
        DWORD current_tick_time=GetTickCount();
        DWORD delta_tick=current_tick_time-last_tick_time;
        m_sceneManager->update(delta_tick);
        last_tick_time=current_tick_time;

        cleardevice();
        m_sceneManager->draw();
        FlushBatchDraw();

        DWORD frame_end_time=GetTickCount();
        DWORD frame_delta_time=frame_end_time-frame_start_time;
        if(frame_delta_time<1000/FPS){
            Sleep(1000/FPS-frame_delta_time);
        }
    }
    EndBatchDraw();
}

void Game::init() {
    m_r->init();
    initgraph(WIN_WIDTH,WIN_HEIGHT);
}

Game::Game() {
    m_r=Singleton<res>::instanceSP();
    m_sceneManager=Singleton<SceneManager>::instance();
}


