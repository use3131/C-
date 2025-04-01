#define _WIN32_WINNT 0x0600
#include "paint1.h"
#include "load1.h"
#include "box.h"
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "keyboard.h"
#include "camera.h"

void putimage_alpha(int x, int y, int alpha, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    int newX = x - w / 2 + 35;
    int newY = y;
    AlphaBlend(GetImageHDC(NULL), newX, newY, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, static_cast<BYTE>(alpha), AC_SRC_ALPHA });
}

void displayH(player* player, Camera* camera) {
    IMAGE* images[4] = { nullptr };
    displaybox(player->box, camera);
    // 处理动画优先级
    if (player->frame.isDefensing) {
        drawDefense(player, camera);
        return;
    }
    if (player->frame.isDashing) {
        drawDash(player, camera);
        return;
    }
    if (player->frame.isAttacking) {
        drawAttack(player, camera);
        return;
    }
    if (player->frame.isAttackuping) {
        drawAttackup(player, camera);
        return;
    }
    if (player->frame.isAttackremoteing) {
        drawAttackremote(player, camera);
        return;
    }

    int walkFrame = player->frame.walkFrame;
    int drawX = player->box.LLvertex.x - Camera_getX(camera);
    int drawY = player->box.LLvertex.y - Camera_getY(camera);

    if (player->blue == 1) {
        putimage_alpha(drawX, drawY, player->alpha, &walkRight[walkFrame]);
    }
    else if (player->blue == 2) {
        putimage_alpha(drawX, drawY, player->alpha, &walkLeft[walkFrame]);
    }
    return;
}

void drawDefense(player* player, Camera* camera) {
    int drawX = player->box.LLvertex.x - Camera_getX(camera);
    int drawY = player->box.LLvertex.y - Camera_getY(camera) + 15;

    if (player->blue == 1) {
        putimage_alpha(drawX, drawY, player->alpha, &defenseRight[0]);
        player->frame.ignoreKeys1 = false;
    }
    else if (player->blue == 2) {
        putimage_alpha(drawX, drawY, player->alpha, &defenseLeft[0]);
        player->frame.ignoreKeys1 = false;
    }
}

void drawDash(player* player, Camera* camera) {
    int& dashFrame = player->frame.dashFrame;
    int drawX = player->box.LLvertex.x - Camera_getX(camera);
    int drawY = player->box.LLvertex.y - Camera_getY(camera);

    if (player->blue == 1) {
        putimage_alpha(drawX, drawY, player->alpha, &dashRight[dashFrame]);
        putimage_alpha(drawX - 170, drawY - 140, player->alpha, &dashEffectRight[dashFrame]);
    }
    else if (player->blue == 2) {
        putimage_alpha(drawX, drawY, player->alpha, &dashLeft[dashFrame]);
        putimage_alpha(drawX + 170, drawY - 140, player->alpha, &dashEffectLeft[dashFrame]);
    }

    dashFrame++;
    if (dashFrame >= 5) {
        player->frame.isDashing = false;
        player->frame.dashFrame = 0;
    }
}

void drawAttack(player* player, Camera* camera) {
    int& attackFrame = player->frame.attackFrame;
    int drawX = player->box.LLvertex.x - Camera_getX(camera);
    int drawY = player->box.LLvertex.y - Camera_getY(camera);
    if (player->blue == 1) {
        putimage_alpha(drawX, drawY, player->alpha, &attackRight[attackFrame]);
    }
    else if (player->blue == 2) {
        putimage_alpha(drawX, drawY, player->alpha, &attackLeft[attackFrame]);
    }
    attackFrame++;
    if (attackFrame >= 3) {
        player->frame.isAttacking = false;
        player->frame.attackFrame = 0;
    }
}

void drawAttackup(player* player, Camera* camera) {
    int& attackupFrame = player->frame.attackupFrame;
    int drawX = player->box.LLvertex.x - Camera_getX(camera);
    int drawY = player->box.LLvertex.y - Camera_getY(camera);

    if (player->blue == 1) {
        putimage_alpha(drawX, drawY, player->alpha, &attackupRight[attackupFrame]);
    }
    else if (player->blue == 2) {
        putimage_alpha(drawX, drawY, player->alpha, &attackupLeft[attackupFrame]);
    }

    attackupFrame++;
    if (attackupFrame >= 5) {
        player->frame.isAttackuping = false;
        player->frame.attackupFrame = 0;
    }
}

void drawAttackremote(player* player, Camera* camera) {
    int& attackremoteFrame = player->frame.attackremoteFrame;
    int drawX = player->box.LLvertex.x - Camera_getX(camera);
    int drawY = player->box.LLvertex.y - Camera_getY(camera);

    if (player->blue == 1) {
        putimage_alpha(drawX, drawY, player->alpha, &attackremoteRight[attackremoteFrame]);
        if (attackremoteFrame >= 8 && attackremoteFrame <= 13) {
            putimage_alpha(drawX + 160, drawY + 40, player->alpha, &attackremoteEffectRight[attackremoteFrame - 8]);
        }
    }
    else if (player->blue == 2) {
        putimage_alpha(drawX, drawY, player->alpha, &attackremoteLeft[attackremoteFrame]);
        if (attackremoteFrame >= 8 && attackremoteFrame <= 13) {
            putimage_alpha(drawX - 160, drawY + 40, player->alpha, &attackremoteEffectLeft[attackremoteFrame - 8]);
        }
    }

    attackremoteFrame++;
    if (attackremoteFrame >= 20) {
        player->frame.isAttackremoteing = false;
        player->frame.attackremoteFrame = 0;
        player->frame.ignoreKeys2 = false;
    }
}
