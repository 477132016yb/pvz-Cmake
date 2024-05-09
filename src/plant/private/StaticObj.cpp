//
// Created by yb on 2024/5/9.
//

#include "../public/StaticObj.h"

void StaticObj::draw() {
    putimagePNG(m_x,m_y,m_img);
}

void StaticObj::update(int delta) {
    Object::update(delta);
}

void StaticObj::setImage(IMAGE *img) {
    m_img = img ;
}
