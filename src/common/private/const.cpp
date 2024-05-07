//
// Created by yb on 2024/5/7.
//
#include "const.h"
using namespace yb;
bool yb::checkHit(int x, int y, int objX, int objy, int objW, int objH) {
    return x>objX&&x<objX+objW&&y>objy&&y<objy+objH;
}

