//
// Created by yb on 2024/5/7.
//
#include "const.h"
namespace yb{
    bool checkHit(int x, int y, int objX, int objy, int objW, int objH) {
        return x>objX&&x<objX+objW&&y>objy&&y<objy+objH;
    }
    bool checkHitX(int x,int objX,int objW){
        return x>objX&&x<objX+objW;
    }
    std::vector<int> plantCostList = {100,50};
    std::vector<int> plantCoolTimeList = {100,100};
    std::vector<const char*>plantNameList={
    "PeaShooter","SunFlower"
    };
    std::vector<const char*>zombieNameList={
            "NormalZombie","RoadBlockZombie"
    };
}
