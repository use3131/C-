#pragma once
#include "box.h" 
static DWORD64 lastPressTimeU = 0;
static const DWORD64 ignoreDuration = 1200;

#define BIG_RECT_LEFT 30
#define BIG_RECT_TOP 1000
#define BIG_RECT_RIGHT 1670
#define BIG_RECT_BOTTOM 100
#define FLOOR 150

// 定义运动常量
#define X_MAX_SPEED 10//水平最大速度应该是加速度的倍数
#define X_ACCELERATION 5
#define JUMP_POWER 60.0F //跳跃瞬时初速度
#define ACCELERATION_OF_GRAVITY -7.0F // 重力加速度

// 定义状态常量
#define PLAYER_STATE_DEFAULT 0
#define PLAYER_STATE_JUMP 1
#define PLAYER_STATE_DEAD 3
#define PLAYER_STATE_DOYBLE_JUMP 4
#define PLAYER_STATE_INVINCIBLE 5
#define INVINCIBLE_DURATION 3000 // 无敌状态持续时间，单位为毫秒

#define NIGHTMARE_STATE_DEFAULT 0
#define NIGHTMARE_STATE_CLOAK 1
#define NIGHTMARE_STATE_RELEASE 2
#define NIGHTMARE_STATE_FORESTING 3
#define NIGHTMARE_STATE_BEHEAD 4
#define	NIGHTMARE_STATE_SMASHDOWN 5

// 定义火蝙蝠的状态
#define FIREBAT_STATE_FLYING 0
#define FIREBAT_STATE_INACTIVE 1

// 定义火蝙蝠的数量
#define NUM_FIREBATS 3


#define KEY_STATE_LEFT 1
#define KEY_STATE_RIGHT 2
#define KEY_STATE_LEFT_AND_RIGHT 5
#define KEY_STATE_UP 3
#define KEY_STATE_DOWN 4




void LEFT_AND_RIGHT_ARROWS_Key_Movement(player* player, DWORD64 currentTime, DWORD64 frameDelay);
int Z_X_C_A_S_D_F_SPACE_CTRL_Key_Movements(player* player);

