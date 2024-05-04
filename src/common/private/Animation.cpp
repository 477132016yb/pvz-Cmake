//
// Created by yb on 2024/4/30.
//

#include "Animation.h"

void Animation::reset() {
    m_timer=0;
    m_idx=0;
}

void Animation::setAtlas(Atlas::SP&atlas) {
    reset();
    m_atlas=atlas;
}

void Animation::setLoop(bool flag) {
    m_isLoop=flag;
}

void Animation::setInterval(int ms) {
    m_interval=ms;
}

bool Animation::checkFinished() {
    if(m_isLoop){
        return false;
    }
    return m_idx==m_atlas->getSize()-1;
}

IMAGE *Animation::getImage() {
    return m_atlas->getImage(m_idx);
}

int Animation::getIdxFrame() {
    return m_idx;
}

void Animation::update(int delta) {
    m_timer+=delta;
    if(m_timer>=m_interval){
        m_timer=0;
        m_idx++;
        if(m_idx>=m_atlas->getSize()){
            m_idx=m_isLoop?0:m_atlas->getSize()-1;
        }
        if(!m_isLoop&&m_callback){
            m_callback();
        }
    }
}

void Animation::draw(int x, int y) const {
    putimagePNG(x,y,m_atlas->getImage(m_idx));
}

void Animation::setCallback(std::function<void()>callback) {
    m_callback=callback;
}

