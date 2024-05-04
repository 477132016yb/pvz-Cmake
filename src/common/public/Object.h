//
// Created by yb on 2024/5/2.
//

#ifndef PVZ_OBJECT_H
#define PVZ_OBJECT_H
#include <iostream>
#include <memory>
#include "Camera.h"
#include "Singleton.h"
class Object{
public:
    Object()=default;
    virtual ~Object()=default;
public:
    void SetName(const std::string& cName);
    std::string getName();
public:
    int m_x{},m_y{};
    static const vector2& m_CameraPos;
    virtual void draw(){};
    virtual void update(int delta){};
public:
    std::string className;
};

#endif //PVZ_OBJECT_H
