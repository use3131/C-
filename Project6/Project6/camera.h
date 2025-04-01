#pragma once
typedef struct {
    int screenWidth;
    int screenHeight;
    int mapWidth;
    int mapHeight;
    float x;
    float y;
    float speed;  // 摄像机移动速度
} Camera;

void Camera_init(Camera* camera, int screenWidth, int screenHeight, int mapWidth, int mapHeight, float speed);
void Camera_update(Camera* camera, int playerX, int playerY);
int Camera_getX(const Camera* camera);
int Camera_getY(const Camera* camera);


