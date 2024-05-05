//
// Created by yb on 2024/4/29.
//

#ifndef PVZ_RES_H
#define PVZ_RES_H
#include<vector>
#include"const.h"
#include<easyx.h>
#include "Atlas.h"
class res {
public:
    using SP=std::shared_ptr<res>;
    res();
    void init();
public:
    bool checkfile(const char* name);
    int getFileNum(const char* filePath);

    IMAGE img_bg;
    IMAGE img_menu;
    IMAGE img_PanelBackGround;
    IMAGE img_selectBar,img_gameBar;
    IMAGE img_selectCardMask,img_gameCardMask;
    std::vector<IMAGE>imgs_startButton;
    std::vector<IMAGE>imgs_fightButton;
    std::vector<IMAGE>imgs_selectCard,imgs_gameCard;
    std::vector<Atlas>atls_plants;
    Atlas atl_sunShine;
};


#endif //PVZ_RES_H
