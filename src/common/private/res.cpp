//
// Created by yb on 2024/4/29.
//

#include "res.h"
std::vector<const char*>buttonName{
        "idle","hovered","pushed"
};
void res::init() {
    loadimage(&img_bg,"res/map/bg.jpg");
    loadimage(&img_menu,"res/map/menu.png");
    loadimage(&img_PanelBackGround,"res/map/PanelBackGround.png");
    loadimage(&img_gameBar,"res/imgs/gameBar.png");
    loadimage(&img_selectBar,"res/imgs/selectBar.png");
    loadimage(&img_shovel,"res/imgs/shovel.png");
    loadimage(&img_shovelSlot,"res/imgs/shovelSlot.png");
    loadimage(&img_v,"res/imgs/1.png");

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

    for(int i=0;i<imgs_vriPlantVec.size();i++){
        TCHAR path[64];
        sprintf_s(path,"res/imgs/vritual/%d.png",i+1);
        loadimage(&imgs_vriPlantVec[i],path);
    }
    for(int i=0;i<imgs_selectCard.size();i++){
        TCHAR path[64];
        sprintf_s(path,"res/Cards/%d.png",i+1);
        loadimage(&imgs_selectCard[i],path,50,72);
        loadimage(&imgs_gameCard[i],path,60,85);
    }
    loadimage(&img_selectCardMask,"res/imgs/cardMask.png",50,72);
    loadimage(&img_gameCardMask,"res/imgs/cardLoad.png",60,85);

    for(int i=0;i<atls_plants.size();i++){
        TCHAR path[64];
        sprintf_s(path,"res/plant/%s",yb::plantNameList[i]);
        int num= getFileNum(path);
        atls_plants[i].loadFromFile(path,num);
    }
    atl_sunShine.loadFromFile("res/sunshine",getFileNum("res/sunshine"));
    atl_cardCoolTime.loadFromFile2("res/imgs/cardCoolTime",getFileNum("res/imgs/cardCoolTime"));
}

bool res::checkfile(const char *name) {
    FILE* fp = fopen(name, "r");
    if (fp) { fclose(fp); }
    return fp != NULL;
}

res::res() {
    atls_plants.resize(PLANT_COUNT);
    imgs_startButton.resize(3);
    imgs_fightButton.resize(3);
    imgs_selectCard.resize(getFileNum("res/Cards/"));
    imgs_gameCard.resize(getFileNum("res/Cards/"));
    imgs_vriPlantVec.resize(getFileNum("res/imgs/vritual"));
    init();
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
