#define _WIN32_WINNT 0x0600 // Windows Vista or later
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#pragma comment(lib, "Msimg32.lib")
#include "box.h"
#include "paint1.h"
#include "list.h"
#include "load1.h"
#include "keyboard.h"
#include <cstdio>
#include <cstring>
#include <tchar.h> 
#include "collision.h"
#include "camera.h"

const int screenWidth = 1920;
const int screenHeight = 1080;
const int mapWidth = 7680;
const int mapHeight = 1080;
const float cameraSpeed = 0.1f;

int SGREENHEIGHT = 1080;
int intabs(int n) {
    return n < 0 ? -n : n;
}
void drawBloodDrops(int health_point) {
    for (int i = 0; i < health_point; i++) {
        putimage_alpha(10 + i * 50, 870, 255, &bloodDrops[i]); // 添加 alpha 参数
    }
}

// 碰撞检测
// 检查两个矩形是否在X轴上重叠
bool isOverlapX(const box& box1, const box& box2) {
    return (
        (box1.LLvertex.x <= box2.LLvertex.x + box2.width &&
            box1.LLvertex.x >= box2.LLvertex.x)
        || (box1.LLvertex.x + box1.width <= box2.LLvertex.x + box2.width &&
            box1.LLvertex.x + box1.width >= box2.LLvertex.x)
        || (box2.LLvertex.x <= box1.LLvertex.x + box1.width &&
            box2.LLvertex.x >= box1.LLvertex.x)
        || (box2.LLvertex.x + box2.width <= box1.LLvertex.x + box1.width &&
            box2.LLvertex.x + box2.width >= box1.LLvertex.x)
        );
}
// 检查两个矩形是否在Y轴上重叠
bool isOverlapY(const box& box1, const box& box2) {
    return (
        (box1.LLvertex.y <= box2.LLvertex.y + box2.lenth &&
            box1.LLvertex.y >= box2.LLvertex.y)
        || (box1.LLvertex.y + box1.lenth <= box2.LLvertex.y + box2.lenth &&
            box1.LLvertex.y + box1.lenth >= box2.LLvertex.y)
        || (box2.LLvertex.y <= box1.LLvertex.y + box1.lenth &&
            box2.LLvertex.y >= box1.LLvertex.y)
        || (box2.LLvertex.y + box2.lenth <= box1.LLvertex.y + box1.lenth &&
            box2.LLvertex.y + box2.lenth >= box1.LLvertex.y)
        );
}
// 处理重叠时的坐标和速度调整
void handleOverlap(player* player, ObjectList* oblist_ptr) {
    player->state = PLAYER_STATE_JUMP;
    int dy = 0;
    for (int dx = 0; dx < intabs(player->box.velocity.x) || dy < intabs(player->box.velocity.y); dx++, dy++) {
        if (dx < intabs(player->box.velocity.x)) {
            if (player->box.velocity.x > 0) player->box.LLvertex.x++;
            else player->box.LLvertex.x--;
        }
        int flag = 0;
        ObjectList* oblist_ptr_tmp = oblist_ptr;
        for (; oblist_ptr_tmp != NULL; oblist_ptr_tmp = oblist_ptr_tmp->next) {
            if (oblist_ptr_tmp->object.isObstacle && oblist_ptr_tmp->object.type == 0) { // 添加 type 判断
                if (isOverlapX(player->box, oblist_ptr_tmp->object.box) &&
                    isOverlapY(player->box, oblist_ptr_tmp->object.box)) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            if (player->box.velocity.x > 0) player->box.LLvertex.x--;
            else player->box.LLvertex.x++;
            player->box.velocity.x = 0;
        }
        if (dy < intabs(player->box.velocity.y)) {
            if (player->box.velocity.y > 0) player->box.LLvertex.y++;
            else player->box.LLvertex.y--;
        }
        flag = 0;
        oblist_ptr_tmp = oblist_ptr;
        for (; oblist_ptr_tmp != NULL; oblist_ptr_tmp = oblist_ptr_tmp->next) {
            if (oblist_ptr_tmp->object.isObstacle && oblist_ptr_tmp->object.type == 0) { // 添加 type 判断
                if (isOverlapX(player->box, oblist_ptr_tmp->object.box) &&
                    isOverlapY(player->box, oblist_ptr_tmp->object.box)) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            if (player->box.velocity.y > 0) player->box.LLvertex.y--;
            else player->box.LLvertex.y++;
            if (player->box.velocity.y < 0) {
                player->state = PLAYER_STATE_DEFAULT;
                player->remaining_times_of_jump = 1;
            }
            player->box.velocity.y = 0;
        }
    }
}
void handleAttack(player* player, ObjectList* oblist_ptr) {
    if (player->invincible) return; // 无敌状态下不处理攻击
    ObjectList* oblist_ptr_tmp = oblist_ptr;
    while (oblist_ptr_tmp != NULL) {
        if (oblist_ptr_tmp->object.isHarmful == 1) {
            if (isOverlapX(player->box, oblist_ptr_tmp->object.box) &&
                isOverlapY(player->box, oblist_ptr_tmp->object.box)) {
                player->health_point--;
                player->invincible = true;
                player->invincibleStartTime = GetTickCount64();
                player->state = PLAYER_STATE_INVINCIBLE;
            }
        }
        oblist_ptr_tmp = oblist_ptr_tmp->next;
    }
}

int main() {
    DWORD64 currentTime;
    initgraph(1920, SGREENHEIGHT);
    Camera camera;
    Camera_init(&camera, screenWidth, screenHeight, mapWidth, mapHeight, cameraSpeed);
    setorigin(0, SGREENHEIGHT);
    setaspectratio(1, -1);
    //初始化
    nightmare nightmare;
    nightmare.box.LLvertex.x = 1500;
    nightmare.box.LLvertex.y = 100;
    nightmare.box.width = 100;
    nightmare.box.lenth = 150;
    nightmare.state = NIGHTMARE_STATE_CLOAK;
    nightmare.currentFrame = 0;
    nightmare.effectFrame = 0;
    nightmare.alpha = 255;
    nightmare.frameDelays[0] = 100;
    nightmare.frameDelays[1] = 100;
    nightmare.frameDelays[2] = 150;
    nightmare.frameDelays[3] = 250;
    nightmare.frameDelays[4] = 300;
    nightmare.currentAction = 0;

    // 迎面走来的你
    player player;
    player.box.LLvertex.x = 100;
    player.box.LLvertex.y = 400;
    player.box.width = 100;
    player.box.lenth = 150;
	player.alpha = 255;
	player.invincible = false;
    player.box.acceleration.y = ACCELERATION_OF_GRAVITY;
    player.remaining_times_of_jump = 1;
    player.state = PLAYER_STATE_JUMP;

    FireBat fireBats[NUM_FIREBATS];
    for (int i = 0; i < NUM_FIREBATS; i++) {
        fireBats[i].box.LLvertex.x = nightmare.box.LLvertex.x;
        fireBats[i].box.LLvertex.y = nightmare.box.LLvertex.y;
        fireBats[i].box.width = 50;
        fireBats[i].box.lenth = 50;
        fireBats[i].state = FIREBAT_STATE_INACTIVE;
        fireBats[i].currentFrame = 0;
        fireBats[i].effectFrame = 0;
        fireBats[i].lastFrameTime = GetTickCount64();
        fireBats[i].frameDelay = 80;
        fireBats[i].flightPath = i;
        fireBats[i].lastFireBatReleaseTime = 0; // 初始化上一次释放火蝙蝠的时间
        fireBats[i].fireBatReleaseInterval = 700; // 初始化火蝙蝠释放的时间间隔（毫秒）
    }

    CreatObject(0, 60, 4000, 30, 1, 0, 0, 1);
    CreatObject(500, 200, 100, 100, 1, 0, 0, 2);
    CreatObject(700, 400, 100, 100, 1, 0, 0, 3);
    CreatObject(4000, 200, 100, 100, 1, 0, 0, 4);


    spike spike = { 0,0, 0, false, {300, 600, 900, 1200, 1500, 1800, 0} };
    int frameDelay = 50;
    load1();
    BeginBatchDraw();
    while (1) {
        CreatObject(1500, 100, 100, 250, 1, 1, 1, 5);
        currentTime = GetTickCount64();
        Camera_update(&camera, static_cast<int>(player.box.LLvertex.x), static_cast<int>(player.box.LLvertex.y)); // 更新相机位置
        cleardevice();
        putimage(-Camera_getX(&camera), -Camera_getY(&camera), &background);
        drawBloodDrops(player.health_point);



        switch (nightmare.state) {
        case NIGHTMARE_STATE_DEFAULT:
            nightmare.currentAction = 0;
            if (GetTickCount64() - nightmare.lastFrameTime >= nightmare.frameDelays[nightmare.currentAction]) {
                nightmare.currentFrame = (nightmare.currentFrame + 1) % 12; // 12帧动画
                nightmare.lastFrameTime = GetTickCount64();
            }

            if (nightmare.blue == 1) {
                putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &idleRight[nightmare.currentFrame]);
            }
            else {
                putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &idleLeft[nightmare.currentFrame]);
            }
            break;

        case NIGHTMARE_STATE_CLOAK:
            nightmare.currentAction = 1;
            if (nightmare.currentFrame < 7 && (spike.stage == 0)) {
                if (GetTickCount64() - nightmare.lastFrameTime >= nightmare.frameDelays[nightmare.currentAction]) {
                    nightmare.currentFrame++;
                    nightmare.lastFrameTime = GetTickCount64();
                }
                if (nightmare.blue == 1) {
                    putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &StartSpikeRight[nightmare.currentFrame]);
                }
                else {
                    putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &StartSpikeLeft[nightmare.currentFrame]);
                }
                if (nightmare.currentFrame == 6) {
                    spike.stage = 1;
                    nightmare.currentFrame = 0;
                }
            }
            if (spike.stage == 1) {
                // 初始化地刺
                if (!spike.spikesInitialized) {
                    spike.spikeFrame = 0;
                    spike.lastSpikeFrameTime = GetTickCount64();
                    spike.spikesInitialized = true;
                }

                // 循环播放地刺动画
                if (GetTickCount64() - spike.lastSpikeFrameTime >= 100) { // 控制地刺动画帧间隔
                    spike.spikeFrame = (spike.spikeFrame + 1) % 14;
                    spike.lastSpikeFrameTime = GetTickCount64();
                }

                if (spike.spikeFrame == 13) {
                    spike.stage = 0;
                    nightmare.state = NIGHTMARE_STATE_RELEASE;
                }

                // 显示地刺
                for (int i = 0; i < 7; i++) {
                    putimage_alpha(spike.spikePositions[i] - Camera_getX(&camera), 0 - Camera_getY(&camera), nightmare.alpha, &SpikeAnimation[spike.spikeFrame]);
                }

                // 显示nightmare的3帧动画
                if (GetTickCount64() - nightmare.lastFrameTime >= nightmare.frameDelays[nightmare.currentAction]) {
                    nightmare.currentFrame = (nightmare.currentFrame + 1) % 3;
                    nightmare.lastFrameTime = GetTickCount64();
                }
                if (nightmare.blue == 1) {
                    putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &CloakAnimationRight[nightmare.currentFrame]);
                }
                else {
                    putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &CloakAnimationLeft[nightmare.currentFrame]);
                }
            }
            break;

        case NIGHTMARE_STATE_RELEASE:
            nightmare.currentAction = 2;
            if (nightmare.currentFrame != 7) {
                if (GetTickCount64() - nightmare.lastFrameTime >= nightmare.frameDelays[nightmare.currentAction]) {
                    nightmare.currentFrame = (nightmare.currentFrame + 1) % 8;
                    nightmare.lastFrameTime = GetTickCount64();
                }
            }
            if (nightmare.blue == 1) {
                putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &releaseRight[nightmare.currentFrame]);

            }
            else {
                putimage_alpha(nightmare.box.LLvertex.x - Camera_getX(&camera), nightmare.box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &releaseLeft[nightmare.currentFrame]);
            }
            if (nightmare.currentFrame == 7) {
                DWORD64 currentTime = GetTickCount64();
                if (currentTime - fireBats[0].lastFireBatReleaseTime >= fireBats[0].fireBatReleaseInterval) {
                    for (int i = 0; i < NUM_FIREBATS; i++) {
                        if (fireBats[i].state == FIREBAT_STATE_INACTIVE) {
                            fireBats[i].state = FIREBAT_STATE_FLYING;
                            if (fireBats[i].flightPath == 0) {
                                fireBats[i].box.LLvertex.y += 70; // 高位轨迹
                                CreatObject(nightmare.box.LLvertex.x, nightmare.box.LLvertex.y + 70, 100, 100, 1, 1, 1, 6);
                            }
                            if (fireBats[i].flightPath == 1) {
                                fireBats[i].box.LLvertex.y += 30; // 高位轨迹
                                CreatObject(nightmare.box.LLvertex.x, nightmare.box.LLvertex.y + 30, 100, 100, 1, 1, 1, 7);
                            }
                            if (fireBats[i].flightPath == 2) {
                                fireBats[i].box.LLvertex.y += 110; // 低位轨迹
                                CreatObject(nightmare.box.LLvertex.x, nightmare.box.LLvertex.y + 110, 100, 100, 1, 1, 1, 8);
                            }
                            fireBats[i].lastFrameTime = GetTickCount64();
                            fireBats[0].lastFireBatReleaseTime = currentTime;
                            break;
                        }
                    }
                }
            }


            for (int i = 0; i < NUM_FIREBATS; i++) {
                if (fireBats[i].state == FIREBAT_STATE_FLYING) {
                    if (GetTickCount64() - fireBats[i].lastFrameTime >= fireBats[i].frameDelay) {
                        fireBats[i].currentFrame = (fireBats[i].currentFrame + 1) % 5;
                        fireBats[i].lastFrameTime = GetTickCount64();
                    }

                    fireBats[i].box.LLvertex.x -= 15;
                    updateObject(6 + i, fireBats[i].box.LLvertex.x -= 15, fireBats[i].box.LLvertex.y);
                    if (fireBats[i].box.LLvertex.x > screenWidth) {
                        fireBats[i].state = FIREBAT_STATE_INACTIVE;
                    }

                    if (nightmare.blue == 1) {
                        putimage_alpha(fireBats[i].box.LLvertex.x - Camera_getX(&camera), fireBats[i].box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &fireBatRight[fireBats[i].currentFrame]);
                    }
                    else {
                        putimage_alpha(fireBats[i].box.LLvertex.x - Camera_getX(&camera), fireBats[i].box.LLvertex.y - Camera_getY(&camera), nightmare.alpha, &fireBatLeft[fireBats[i].currentFrame]);
                    }
                }
            }
            break;

        case NIGHTMARE_STATE_FORESTING:
            nightmare.currentAction = 3;
            // 处理 NIGHTMARE_STATE_FORESTING 状态
            break;

        case NIGHTMARE_STATE_BEHEAD:
            nightmare.currentAction = 4;
            // 处理 NIGHTMARE_STATE_BEHEAD 状态
            break;

        case NIGHTMARE_STATE_SMASHDOWN:
            // 处理 NIGHTMARE_STATE_SMASHDOWN 状态
            break;

        default:
            // 处理所有其他未定义的状态
            break;
        }


        switch (player.state) {
        case PLAYER_STATE_DEFAULT:
            player.box.acceleration.y = 0;
            accelerate(&player.box);
            if (player.box.velocity.x || player.box.velocity.y) {
                handleOverlap(&player, head_OfObLst->next);
            }
            break;

        case PLAYER_STATE_JUMP:
            player.box.acceleration.y = ACCELERATION_OF_GRAVITY;
            accelerate(&player.box);
            if (player.box.velocity.x || player.box.velocity.y) {
                handleOverlap(&player, head_OfObLst->next);
            }
            break;
        case PLAYER_STATE_INVINCIBLE:
            player.box.acceleration.y = 0;
            accelerate(&player.box);
            if (player.box.velocity.x || player.box.velocity.y) {
                handleOverlap(&player, head_OfObLst->next);
            }
            if (GetTickCount64() - player.invincibleStartTime >= INVINCIBLE_DURATION) {
                player.invincible = false;
                player.alpha = 255;
                player.state = PLAYER_STATE_DEFAULT;
            }
            else {
                if ((GetTickCount64() / 100) % 2 == 0) {
                    player.alpha = 0;
                }
                else {
                    player.alpha = 255;
                }
            }
            break;
            
        case PLAYER_STATE_DEAD:
            break;
        }

        Z_X_C_A_S_D_F_SPACE_CTRL_Key_Movements(&player);
        LEFT_AND_RIGHT_ARROWS_Key_Movement(&player, currentTime, frameDelay);
        // displayH(&player, &camera);
        handleAttack(&player, head_OfObLst->next);
        displayH(&player, &camera);
        //displaybox(nightmare.box, &camera);
        setlinecolor(YELLOW);
        drawObstacles(head_OfObLst->next, &camera);
        setlinecolor(WHITE);
        Sleep(3);
        FlushBatchDraw();
    }

    // 关闭图形窗口
    closegraph();
    return 0;
}

