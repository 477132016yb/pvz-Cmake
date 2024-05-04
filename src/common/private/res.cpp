//
// Created by yb on 2024/4/29.
//

#include "res.h"
std::vector<const char*>plantNameList{
        "PeaShooter","SunFlower"
};
std::vector<const char*>buttonName{
        "idle","hovered","pushed"
};
#define PLANT_COUNT plantNameList.size()
void res::init() {
    loadimage(&img_bg,"res/map/bg.jpg");
    loadimage(&img_menu,"res/map/menu.png");
    loadimage(&img_PanelBackGround,"res/map/PanelBackGround.png");
    loadimage(&img_ChooserBackground,"res/map/ChooserBackground.png");

    for(int i=0;i<imgs_startButton.size();i++){
        TCHAR path[64];
        sprintf_s(path,"res/map/start_%s.png",buttonName[i]);
        loadimage(&imgs_startButton[i],path);
    }
    for(int i=0;i<imgs_fightButton.size();i++){
        TCHAR path[64];
        sprintf_s(path,"res/map/fight_%s.png",buttonName[i]);
        loadimage(&imgs_fightButton[i],path);
    }

    for(int i=0;i<imgs_card.size();i++){
        TCHAR path[64];
        sprintf_s(path,"res/Cards/%d.png",i+1);
        loadimage(&imgs_card[i],path,50,72);
    }
    loadimage(&img_cardMask,"res/imgs/cardMask.png",50,72);

    for(int i=0;i<atl_plants.size();i++){
        TCHAR path[64];
        sprintf_s(path,"res/plant/%s",plantNameList[i]);
        int num= getFileNum(path);
        atl_plants[i].loadFromFile(path,num);
    }
}

bool res::checkfile(const char *name) {
    FILE* fp = fopen(name, "r");
    if (fp) { fclose(fp); }
    return fp != NULL;
}

res::res() {
    atl_plants.resize(PLANT_COUNT);
    imgs_startButton.resize(3);
    imgs_fightButton.resize(3);
    imgs_card.resize(getFileNum("res/Cards/"));
}

int res::getFileNum(const char *filePath) {
    int num=0;
    char name[64];
    while(true){
        sprintf_s(name, "%s/%d.png", filePath,num+1);
        if (checkfile(name)) {
            num++;
        }
        else { break; }
    }
    return num;
}
