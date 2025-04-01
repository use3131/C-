#pragma once
#include <graphics.h>
#include "camera.h"

// ���� scene ����
typedef struct scene {
    int music;
    int background;
} scene;

// ���� box ����
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
    bool invincible = false; // �޵�״̬��־
    DWORD64 invincibleStartTime; // �޵�״̬��ʼʱ��
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
    DWORD64 frameDelays[5]; // ������5�ֲ�ͬ�Ķ���
    int currentAction; // ��ǰ��������
} nightmare;


typedef struct {
    box box;
    int state;
    int currentFrame;
	int effectFrame;
    DWORD64 lastFrameTime;
    DWORD64 frameDelay;
    int flightPath;
    DWORD64 lastFireBatReleaseTime; // ��¼��һ���ͷŻ������ʱ��
    DWORD64 fireBatReleaseInterval; // �趨�������ͷŵ�ʱ���������룩
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

// �� box ��ʾ�ڻ�����
void displaybox(box box, Camera* camera);

// box �ļ���
void accelerate(box* box);

// box ���˶�
void movebox(box* box);
