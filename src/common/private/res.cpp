//
// Created by yb on 2024/4/29.
//

#include "res.h"
std::vector<const char*>buttonName{
        "idle","hovered","pushed"
};
std::vector<const char*>zombieStatusName{
        "Stand","Walking","Attack","FallDown"
};
void res::init() {
    loadimage(&img_bg,"res/map/bg.jpg");
    loadimage(&img_menu,"res/map/menu.png");
    loadimage(&img_PanelBackGround,"res/map/PanelBackGround.png");
    loadimage(&img_gameBar,"res/imgs/gameBar.png");
    loadimage(&img_selectBar,"res/imgs/selectBar.png");
    loadimage(&img_shovel,"res/imgs/shovel.png");
    loadimage(&img_shovelSlot,"res/imgs/shovelSlot.png");
    loadimage(&img_bulletNormal,"res/imgs/bullets/Normal.png");
    loadimage(&img_bulletCool,"res/imgs/bullets/Cool.png");
    loadimage(&img_bulletFire,"res/imgs/bullets/Fire.png");
    for (int i = 0; i < imgs_BlastNormal.size(); i++) {
        float k = (i + 1) * 0.2;
        loadimage(&imgs_BlastNormal[i], "res/imgs/bullets/bullet_blast.png",
                  img_bulletNormal.getwidth() * k, img_bulletNormal.getheight() * k, true);
        loadimage(&imgs_BlastCool[i], "res/imgs/bullets/bullet_blast_bing.png",
                  img_bulletCool.getwidth() * k, img_bulletCool.getheight() * k, true);
    }


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

    for(int i=0;i<atls_zombies.size();i++){
        for(int j=0;j<atls_zombies[i].size();j++){
            TCHAR path[64];
            sprintf_s(path,"res/zombie/%s/%s",yb::zombieNameList[i],zombieStatusName[j]);
            int num = getFileNum(path);
            atls_zombies[i][j].loadFromFile(path,num);
        }
    }
    atl_zombieAshes.loadFromFile("res/zombie/Ashes", getFileNum("res/zombie/Ashes"));
    atl_zombieHead.loadFromFile("res/zombie/Head", getFileNum("res/zombie/Head"));
}

bool res::checkfile(const char *name) {
    FILE* fp = fopen(name, "r");
    if (fp) { fclose(fp); }
    return fp != NULL;
}

res::res() {
    atls_plants.resize(PLANT_COUNT);
    atls_zombies=std::vector<std::vector<Atlas>>(ZOMBIE_COUNT,std::vector<Atlas>(zombieStatusName.size()));
    imgs_startButton.resize(3);
    imgs_fightButton.resize(3);
    imgs_selectCard.resize(getFileNum("res/Cards/"));
    imgs_gameCard.resize(getFileNum("res/Cards/"));
    imgs_vriPlantVec.resize(getFileNum("res/imgs/vritual"));
    imgs_BlastCool.resize(4);
    imgs_BlastNormal.resize(4);
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
