#pragma once
#include "box.h" 
static DWORD64 lastPressTimeU = 0;
static const DWORD64 ignoreDuration = 1200;

#define BIG_RECT_LEFT 30
#define BIG_RECT_TOP 1000
#define BIG_RECT_RIGHT 1670
#define BIG_RECT_BOTTOM 100
#define FLOOR 150

// �����˶�����
#define X_MAX_SPEED 10//ˮƽ����ٶ�Ӧ���Ǽ��ٶȵı���
#define X_ACCELERATION 5
#define JUMP_POWER 60.0F //��Ծ˲ʱ���ٶ�
#define ACCELERATION_OF_GRAVITY -7.0F // �������ٶ�

// ����״̬����
#define PLAYER_STATE_DEFAULT 0
#define PLAYER_STATE_JUMP 1
#define PLAYER_STATE_DEAD 3
#define PLAYER_STATE_DOYBLE_JUMP 4
#define PLAYER_STATE_INVINCIBLE 5
#define INVINCIBLE_DURATION 3000 // �޵�״̬����ʱ�䣬��λΪ����

#define NIGHTMARE_STATE_DEFAULT 0
#define NIGHTMARE_STATE_CLOAK 1
#define NIGHTMARE_STATE_RELEASE 2
#define NIGHTMARE_STATE_FORESTING 3
#define NIGHTMARE_STATE_BEHEAD 4
#define	NIGHTMARE_STATE_SMASHDOWN 5

// ����������״̬
#define FIREBAT_STATE_FLYING 0
#define FIREBAT_STATE_INACTIVE 1

// ��������������
#define NUM_FIREBATS 3


#define KEY_STATE_LEFT 1
#define KEY_STATE_RIGHT 2
#define KEY_STATE_LEFT_AND_RIGHT 5
#define KEY_STATE_UP 3
#define KEY_STATE_DOWN 4




void LEFT_AND_RIGHT_ARROWS_Key_Movement(player* player, DWORD64 currentTime, DWORD64 frameDelay);
int Z_X_C_A_S_D_F_SPACE_CTRL_Key_Movements(player* player);

