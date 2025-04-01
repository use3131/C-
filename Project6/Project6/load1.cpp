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
IMAGE background; // ��ӱ���ͼ��

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
IMAGE CastEffect[4];  // ��� CastEffectLeft
IMAGE bloodDrops[6];

// ��ֱ��תͼ��
void flipImageVertically(IMAGE& img) {
    int width = img.getwidth();
    int height = img.getheight();
    DWORD* buffer = GetImageBuffer(&img);  // ��ȡͼ������ػ�����

    // ����һ����ʱ���������ڷ�ת
    DWORD* tempBuffer = new DWORD[width * height];

    // ��ԭʼͼ�����ݸ��Ƶ���ʱ������
    memcpy(tempBuffer, buffer, width * height * sizeof(DWORD));

    // ��תͼ������
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int srcIndex = (height - y - 1) * width + x;
            int dstIndex = y * width + x;
            buffer[dstIndex] = tempBuffer[srcIndex];
        }
    }

    delete[] tempBuffer;  // �ͷ���ʱ������
}

void load1() {
    _TCHAR path[256];

    // ���ز���ת����ͼ��
    loadimage(&background, _T("C:\\Users\\38830\\Desktop\\12.png"));
    flipImageVertically(background);

    for (int i = 0; i < 4; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Walk\\%d.png"), i);
        loadimage(&walkRight[i], path);
        flipImageVertically(walkRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Walk\\1%d.png"), i);
        loadimage(&walkLeft[i], path);
        flipImageVertically(walkLeft[i]);  // ��תͼ��
    }

    for (int i = 0; i < 12; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\NightMare\\Idle\\%d.png"), i);
        loadimage(&idleRight[i], path);
        flipImageVertically(idleRight[i]);  // ��תͼ��
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
        flipImageVertically(CloakAnimationRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\Spike\\%d.png"), i);
        loadimage(&CloakAnimationLeft[i], path);
        flipImageVertically(CloakAnimationLeft[i]);
    }

    for (int i = 0; i < 14; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\Spike\\Start\\%d.png"), i);
        loadimage(&SpikeAnimation[i], path);
        flipImageVertically(SpikeAnimation[i]);  // ��תͼ��
    }

    for (int i = 0; i < 7; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\StartSpike\\%d.png"), i);
        loadimage(&StartSpikeRight[i], path);
        flipImageVertically(StartSpikeRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\StartSpike\\%d.png"), i);
        loadimage(&StartSpikeLeft[i], path);
        flipImageVertically(StartSpikeLeft[i]);
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\FireBat\\Idle\\%d.png"), i);
        loadimage(&fireBatRight[i], path);
        flipImageVertically(fireBatRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\FireBat\\Idle\\%d.png"), i);
        loadimage(&fireBatLeft[i], path);
        flipImageVertically(fireBatLeft[i]);
    }

    for (int i = 0; i < 8; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\Cast\\%d.png"), i);
        loadimage(&releaseRight[i], path);
        flipImageVertically(releaseRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("C:\\Users\\38830\\Desktop\\asset\\FullNightMare\\NightMare\\Cast\\%d.png"), i);
        loadimage(&releaseLeft[i], path);
        flipImageVertically(releaseLeft[i]);
    }

    for (int i = 0; i < 20; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\%d.png"), i);
        loadimage(&attackremoteRight[i], path);
        flipImageVertically(attackremoteRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\11%d.png"), i);
        loadimage(&attackremoteLeft[i], path);
        flipImageVertically(attackremoteLeft[i]);  // ��תͼ��
    }

    for (int i = 0; i < 6; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\12%d.png"), i);
        loadimage(&attackremoteEffectRight[i], path);
        flipImageVertically(attackremoteEffectRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\RemoteDisSkill\\13%d.png"), i);
        loadimage(&attackremoteEffectLeft[i], path);
        flipImageVertically(attackremoteEffectLeft[i]);  // ��תͼ��
    }

    for (int i = 0; i < 3; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Attack_0\\%d.png"), i);
        loadimage(&attackRight[i], path);
        flipImageVertically(attackRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Attack_0\\1%d.png"), i);
        loadimage(&attackLeft[i], path);
        flipImageVertically(attackLeft[i]);  // ��תͼ��
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\AttackUp\\%d.png"), i);
        loadimage(&attackupRight[i], path);
        flipImageVertically(attackupRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\AttackUp\\1%d.png"), i);
        loadimage(&attackupLeft[i], path);
        flipImageVertically(attackupLeft[i]);  // ��תͼ��
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Dash\\%d.png"), i);
        loadimage(&dashRight[i], path);
        flipImageVertically(dashRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Dash\\1%d.png"), i);
        loadimage(&dashLeft[i], path);
        flipImageVertically(dashLeft[i]);  // ��תͼ��
    }

    for (int i = 0; i < 5; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\DashEffect\\%d.png"), i);
        loadimage(&dashEffectRight[i], path);
        flipImageVertically(dashEffectRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\DashEffect\\1%d.png"), i);
        loadimage(&dashEffectLeft[i], path);
        flipImageVertically(dashEffectLeft[i]);  // ��תͼ��
    }

    for (int i = 0; i < 2; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Defend\\%d.png"), i);
        loadimage(&defenseRight[i], path);
        flipImageVertically(defenseRight[i]);  // ��תͼ��
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\Player\\Defend\\1%d.png"), i);
        loadimage(&defenseLeft[i], path);
        flipImageVertically(defenseLeft[i]);  // ��תͼ��
    }
    // ����Ѫ��ͼ��
    for (int i = 0; i < 6; ++i) {
        _stprintf_s(path, sizeof(path) / sizeof(_TCHAR), _T("D:\\Bleach vs Naruto\\SilkSong-main\\SilkSong\\Asset\\Animations\\UI\\BloodIdle\\%d.png"), i);
        loadimage(&bloodDrops[i], path);
        flipImageVertically(bloodDrops[i]);  // ��תͼ��
    }
}

