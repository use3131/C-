#pragma once
#include <graphics.h>

// 声明外部 IMAGE 对象数组
extern IMAGE walkRight[4];
extern IMAGE walkLeft[4];
// extern IMAGE jumpRight[6];
// extern IMAGE jumpLeft[6];

// 声明攻击动画的图片资源
extern IMAGE attackRight[3];
extern IMAGE attackLeft[3];
extern IMAGE attackremoteRight[20];
extern IMAGE attackremoteLeft[20];
extern IMAGE attackupRight[5];
extern IMAGE attackupLeft[5];
extern IMAGE defenseRight[2];
extern IMAGE defenseLeft[2];

// 文件: load1.h
extern IMAGE attackremoteEffectRight[6];
extern IMAGE attackremoteEffectLeft[6];

extern IMAGE dashLeft[5];
extern IMAGE dashRight[5];
// 声明攻击效果的图片资源
extern IMAGE dashEffectRight[5];  // 向右攻击效果的四帧
extern IMAGE dashEffectLeft[5];   // 向左攻击效果的四帧

extern IMAGE idleRight[12];
extern IMAGE idleLeft[12];
extern IMAGE releaseRight[8];
extern IMAGE releaseLeft[8];
extern IMAGE fireBatRight[5];
extern IMAGE fireBatLeft[5];
extern IMAGE StartSpikeRight[7];
extern IMAGE StartSpikeLeft[7];
extern IMAGE CloakAnimationRight[3];
extern IMAGE CloakAnimationLeft[3];
extern IMAGE SpikeAnimation[14];
extern IMAGE CastEffect[4];
extern IMAGE bloodDrops[6];
// 声明背景图像
extern IMAGE background;
void load1();

