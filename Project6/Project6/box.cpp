#include "box.h"

void displaybox(box box, Camera* camera) {
    int adjustedX = box.LLvertex.x - camera->x;
    int adjustedY = box.LLvertex.y - camera->y;
    rectangle(adjustedX, adjustedY , adjustedX + box.width, adjustedY + box.lenth);
}


void accelerate(box* box) {
    box->velocity.x += box->acceleration.x;
    box->velocity.y += box->acceleration.y;
}

void movebox(box* box) {
    box->LLvertex.x += box->velocity.x;
    box->LLvertex.y += box->velocity.y;
}
