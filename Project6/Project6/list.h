#pragma once
#include"box.h"

typedef struct object {
	box box;
	int isObstacle = 1;
	int isHarmful = 0;
	int num = 0;
	int type = 0;//real=0,ghost=1
}object;

typedef struct ObjectList {
	object object;
	struct ObjectList* next = NULL;
	struct ObjectList* last = NULL;
}ObjectList;

ObjectList zero;
ObjectList* head_OfObLst = &zero;
ObjectList* tail_OfObLst = &zero;

ObjectList* CreatObject(int x, int y, int width, int lenth, int isObstacle, int isHarmful, int type, int num) {
	tail_OfObLst->next = (ObjectList*)malloc(sizeof(ObjectList));
	tail_OfObLst->next->last = tail_OfObLst;
	tail_OfObLst->next->next = NULL;
	tail_OfObLst = tail_OfObLst->next;
	tail_OfObLst->object.box.LLvertex.x = x;
	tail_OfObLst->object.box.LLvertex.y = y;
	tail_OfObLst->object.box.width = width;
	tail_OfObLst->object.box.lenth = lenth;
	tail_OfObLst->object.isHarmful = isHarmful;
	tail_OfObLst->object.isObstacle = isObstacle;
	tail_OfObLst->object.num = num;
	tail_OfObLst->object.type = type; // 设置类别
	return tail_OfObLst;
}

void updateObject(int num, int newX, int newY) {
	ObjectList* current = head_OfObLst->next;
	while (current != NULL) {
		if (current->object.num == num) { // 修改这里
			current->object.box.LLvertex.x = newX;
			current->object.box.LLvertex.y = newY;
			break;
		}
		current = current->next;
	}
}


void DeleteObject(ObjectList* ptr) {

}

void drawObstacles(ObjectList* oblist_ptr, Camera* camera) {
	ObjectList* oblist_ptr_tmp = oblist_ptr;
	for (; oblist_ptr_tmp != NULL; oblist_ptr_tmp = oblist_ptr_tmp->next) {
		if (oblist_ptr_tmp->object.isObstacle) {
			displaybox(oblist_ptr_tmp->object.box, camera);
		}
	}
}
