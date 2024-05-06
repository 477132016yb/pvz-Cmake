//
// Created by yb on 2024/4/28.
//

#ifndef PVZ_CONST_H
#define PVZ_CONST_H
#include <iostream>
#include <vector>
#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define FPS 90
#define LOG(a) std::cout<<a<<std::endl
typedef unsigned long long uint64_t;
template<typename T>
void clearVector(std::vector<T*>&vec){
    for(T*& a:vec){
        if(a&&!a->m_used){
            delete a;
            a= nullptr;
            std::swap(a,vec.back());
            vec.pop_back();
        }
    }
};
template<typename T>
void updateVector(std::vector<T*>&vec,int delta){
    for(T*& a:vec){
        if(a){
            a->update(delta);
        }
    }
};
template<typename T>
void drawVector(std::vector<T*>&vec){
    for(T*& a:vec){
        if(a){
            a->draw();
        }
    }
};
#endif //PVZ_CONST_H
