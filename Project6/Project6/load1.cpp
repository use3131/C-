#include "load1.h"
#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <tchar.h> 

IMAGE walkRight[4];
IMAGE walkLeft[4];
IMAGE attackEffectRight[4];
IMAGE attackEffectLeft[4];
IMAGE attackRight[3];
IMAGE attackLeft[3];
IMAGE attackremoteEffectRight[6];
IMAGE attackremoteEffectLeft[6];
IMAGE attackremoteRight[20];
IMAGE attackremoteLeft[20];
IMAGE dashEffectRight[5];
IMAGE dashEffectLeft[5];
IMAGE dashRight[5];
IMAGE dashLeft[5];
IMAGE attackupRight[5];
IMAGE attackupLeft[5];
IMAGE defenseRight[2];
IMAGE defenseLeft[2];
IMAGE background; // 添加背景图像

IMAGE idleRight[12];
IMAGE idleLeft[12];
IMAGE releaseRight[8];
IMAGE releaseLeft[8];
IMAGE fireBatRight[5];
IMAGE fireBatLeft[5];
IMAGE StartSpikeRight[7];
IMAGE StartSpikeLeft[7];
IMAGE CloakAnimationRight[3];
IMAGE CloakAnimationLeft[3];
IMAGE SpikeAnimation[14];
IMAGE CastEffect[4];  // 添加 CastEffectLeft
IMAGE bloodDrops[6];

// 垂直翻转图像
void flipImageVertically(IMAGE& img) {
    int width = img.getwidth();
    int height = img.getheight();
    DWORD* buffer = GetImageBuffer(&img);  // 获取图像的像素缓冲区

    // 创建一个临时缓冲区用于翻转
    DWORD* tempBuffer = new DWORD[width * height];

    // 将原始图像数据复制到临时缓冲区
    memcpy(tempBuffer, buffer, width * height * sizeof(DWORD));

    // 翻转图像数据
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int srcIndex = (height - y - 1) * width + x;
            int dstIndex = y * width + x;
            buffer[dstIndex] = tempBuffer[srcIndex];
        }
    }

    delete[] tempBuffer;  // 释放临时缓冲区
}

void load1() {
    _TCHAR path[256];

    // 加载并翻转背景图像
    loadimage(&background, _T("C:\\Users\\38830\\Desktop\\12.png"));
    flipImageVertically(background);

    for (int i = 0; i < 4; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Walk\\%d.png"), i);
        loadimage(&walkRight[i], path);
        flipImageVertically(walkRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Walk\\1%d.png"), i);
        loadimage(&walkLeft[i], path);
        flipImageVertically(walkLeft[i]);  // 翻转图像
    }

    for (int i = 0; i < 12; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\NightMare\\Idle\\%d.png"), i);
        loadimage(&idleRight[i], path);
        flipImageVertically(idleRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\NightMare\\Idle\\%d.png"), i);
        loadimage(&idleLeft[i], path);
        flipImageVertically(idleLeft[i]);
    }

    for (int i = 0; i < 4; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\CastEffect\\%d.png"), i);
        loadimage(&CastEffect[i], path);
        flipImageVertically(CastEffect[i]);
    }

    for (int i = 0; i < 3; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\Spike\\%d.png"), i);
        loadimage(&CloakAnimationRight[i], path);
        flipImageVertically(CloakAnimationRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\Spike\\%d.png"), i);
        loadimage(&CloakAnimationLeft[i], path);
        flipImageVertically(CloakAnimationLeft[i]);
    }

    for (int i = 0; i < 14; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\Spike\\Start\\%d.png"), i);
        loadimage(&SpikeAnimation[i], path);
        flipImageVertically(SpikeAnimation[i]);  // 翻转图像
    }

    for (int i = 0; i < 7; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\StartSpike\\%d.png"), i);
        loadimage(&StartSpikeRight[i], path);
        flipImageVertically(StartSpikeRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\StartSpike\\%d.png"), i);
        loadimage(&StartSpikeLeft[i], path);
        flipImageVertically(StartSpikeLeft[i]);
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\FireBat\\Idle\\%d.png"), i);
        loadimage(&fireBatRight[i], path);
        flipImageVertically(fireBatRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\FireBat\\Idle\\%d.png"), i);
        loadimage(&fireBatLeft[i], path);
        flipImageVertically(fireBatLeft[i]);
    }

    for (int i = 0; i < 8; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\Cast\\%d.png"), i);
        loadimage(&releaseRight[i], path);
        flipImageVertically(releaseRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\Cast\\%d.png"), i);
        loadimage(&releaseLeft[i], path);
        flipImageVertically(releaseLeft[i]);
    }

    for (int i = 0; i < 20; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\%d.png"), i);
        loadimage(&attackremoteRight[i], path);
        flipImageVertically(attackremoteRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\11%d.png"), i);
        loadimage(&attackremoteLeft[i], path);
        flipImageVertically(attackremoteLeft[i]);  // 翻转图像
    }

    for (int i = 0; i < 6; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\12%d.png"), i);
        loadimage(&attackremoteEffectRight[i], path);
        flipImageVertically(attackremoteEffectRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\13%d.png"), i);
        loadimage(&attackremoteEffectLeft[i], path);
        flipImageVertically(attackremoteEffectLeft[i]);  // 翻转图像
    }

    for (int i = 0; i < 3; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Attack_0\\%d.png"), i);
        loadimage(&attackRight[i], path);
        flipImageVertically(attackRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Attack_0\\1%d.png"), i);
        loadimage(&attackLeft[i], path);
        flipImageVertically(attackLeft[i]);  // 翻转图像
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\AttackUp\\%d.png"), i);
        loadimage(&attackupRight[i], path);
        flipImageVertically(attackupRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\AttackUp\\1%d.png"), i);
        loadimage(&attackupLeft[i], path);
        flipImageVertically(attackupLeft[i]);  // 翻转图像
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Dash\\%d.png"), i);
        loadimage(&dashRight[i], path);
        flipImageVertically(dashRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Dash\\1%d.png"), i);
        loadimage(&dashLeft[i], path);
        flipImageVertically(dashLeft[i]);  // 翻转图像
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\DashEffect\\%d.png"), i);
        loadimage(&dashEffectRight[i], path);
        flipImageVertically(dashEffectRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\DashEffect\\1%d.png"), i);
        loadimage(&dashEffectLeft[i], path);
        flipImageVertically(dashEffectLeft[i]);  // 翻转图像
    }

    for (int i = 0; i < 2; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Defend\\%d.png"), i);
        loadimage(&defenseRight[i], path);
        flipImageVertically(defenseRight[i]);  // 翻转图像
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Defend\\1%d.png"), i);
        loadimage(&defenseLeft[i], path);
        flipImageVertically(defenseLeft[i]);  // 翻转图像
    }
    // 加载血滴图像
    for (int i = 0; i < 6; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\UI\\BloodIdle\\%d.png"), i);
        loadimage(&bloodDrops[i], path);
        flipImageVertically(bloodDrops[i]);  // 翻转图像
    }
}

