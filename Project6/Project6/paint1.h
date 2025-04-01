#pragma once
#include "box.h"
#include "load1.h"
#include "camera.h"

void displayH(player* player, Camera* camera); // ÐÞ¸Äº¯ÊýÉùÃ÷
void drawDefense(player* player, Camera* camera);
void drawDash(player* player, Camera* camera);
void drawAttack(player* player, Camera* camera);
void drawAttackup(player* player, Camera* camera);
void drawAttackremote(player* player, Camera* camera);
void putimage_alpha(int x, int y, int alpha, IMAGE* img);


