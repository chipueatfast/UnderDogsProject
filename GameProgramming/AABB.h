#pragma once
//new 02-11 chipu
#ifndef _AABB_H
#define _AABB_H
#include"GameObject.h"
RECT GetSweptBroadphaseRect(const RECT&);
float CheckCollision(GameObject*, GameObject*); //moving vs static


#endif
