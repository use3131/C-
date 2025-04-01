#include "camera.h"

void Camera_init(Camera* camera, int screenWidth, int screenHeight, int mapWidth, int mapHeight, float speed) {
    camera->screenWidth = screenWidth;
    camera->screenHeight = screenHeight;
    camera->mapWidth = mapWidth;
    camera->mapHeight = mapHeight;
    camera->x = 0;
    camera->y = 0;
    camera->speed = speed;
}

void Camera_update(Camera* camera, int playerX, int playerY) {
    float targetX = playerX - camera->screenWidth / 2;
    float targetY = playerY - camera->screenHeight / 2;

    // ���Բ�ֵ�����ƶ��������Ŀ��λ��
    camera->x += (targetX - camera->x) * camera->speed;
    camera->y += (targetY - camera->y) * camera->speed;

    // ȷ����������ᳬ����ͼ�߽�
    if (camera->x < 0) camera->x = 0;
    if (camera->y < 0) camera->y = 0;
    if (camera->x > camera->mapWidth - camera->screenWidth) camera->x = camera->mapWidth - camera->screenWidth;
    if (camera->y > camera->mapHeight - camera->screenHeight) camera->y = camera->mapHeight - camera->screenHeight;
}

int Camera_getX(const Camera* camera) {
    return (int)camera->x;
}

int Camera_getY(const Camera* camera) {
    return (int)camera->y;
}