#pragma once

/*******************************************
**封装cstdlib的srand()与rand()函数，请确保独占
**next_rand(x)返回0~x-1当中的一个整数，x必须为正
**注意：包含了assert(x>0)
*******************************************/

int next_rand(int);