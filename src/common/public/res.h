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
    IMAGE img_ChooserBackground;
    IMAGE img_cardMask;
    std::vector<IMAGE>imgs_startButton;
    std::vector<IMAGE>imgs_fightButton;
    std::vector<IMAGE>imgs_card;
    std::vector<Atlas>atl_plants;
};


#endif //PVZ_RES_H
