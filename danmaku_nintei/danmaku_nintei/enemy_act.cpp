#include "GV.h"

void act0(){//静止
	enemy.vy = 0;
}

void act1(){//下へ移動
	enemy.vy = 1.12;
}

void act2(){//上へ移動
	enemy.vy = -1.12;
}