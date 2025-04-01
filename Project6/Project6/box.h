#pragma once
#include <graphics.h>
#include "camera.h"

// 定义 scene 类型
typedef struct scene {
    int music;
    int background;
} scene;

// 定义 box 类型
typedef struct bivector {
    int x = 0, y = 0;
} bivector;

typedef struct box {
    int width;
    int lenth;
    int state;
    bivector LLvertex;
    bivector acceleration;
    bivector velocity;
} box;

typedef struct frame {
    bool ignoreKeys1 = false;
    bool ignoreKeys2 = false;
    int walkFrame = 0;
    bool isAttacking = false;
    int attackFrame = 0;
    bool isAttackuping = false;
    int attackupFrame = 0;
    bool isDashing = false;
    int dashFrame = 0;
    bool isAttackremoteing = false;
    int attackremoteFrame = 0;
    bool isDefensing = false;
} frame;

typedef struct player {
    box box;
    int remaining_times_of_jump;
    int health_point = 6;
    int attack_power;
    int soul_point = 3;
    int state;
	int alpha = 255;
    int blue = 1;
    frame frame;
    bool invincible = false; // 无敌状态标志
    DWORD64 invincibleStartTime; // 无敌状态开始时间
} player;


typedef struct nightmare {
    box box;
    int health_point = 6;
    int state;
    int blue = 1;
    int currentFrame;
    int effectFrame;
    int alpha = 255;
    DWORD64 lastFrameTime;
    DWORD64 frameDelays[5]; // 假设有5种不同的动作
    int currentAction; // 当前动作索引
} nightmare;


typedef struct {
    box box;
    int state;
    int currentFrame;
	int effectFrame;
    DWORD64 lastFrameTime;
    DWORD64 frameDelay;
    int flightPath;
    DWORD64 lastFireBatReleaseTime; // 记录上一次释放火蝙蝠的时间
    DWORD64 fireBatReleaseInterval; // 设定火蝙蝠释放的时间间隔（毫秒）
} FireBat;

typedef struct {
    int stage;
    bool spikesInitialized;
    int spikeFrame;
    DWORD64 lastSpikeFrameTime;
    int spikePositions[7];
} spike;





typedef struct game {
    int menu;
    scene first;
    scene second;
} game;

// 将 box 显示在画面上
void displaybox(box box, Camera* camera);

// box 的加速
void accelerate(box* box);

// box 的运动
void movebox(box* box);
