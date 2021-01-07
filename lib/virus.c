#include "virus.h"

static int qtEnemy = 0;

bool checkEnemyLeft(Ship *virus) {
	int livingEnemy = 0;
	for(int j = 0; j < qtEnemy; ++j) {
		if (virus[j].life > 0) {
			livingEnemy++;
		}
	}
	if(livingEnemy > 0) {
		return true;
	}else {
		return false;
	}
}

int enemyNumbers(int level) {
	return level * 2;
}


Ship *initVirus(int level){
	qtEnemy = enemyNumbers(level);
	Ship *virus;
	virus = (Ship*)malloc(qtEnemy*sizeof(Ship));
	if (virus != NULL){
		for (int j = 0; j < qtEnemy; ++j){
			virus[j].x = j*150 + 64;
			virus[j].y = (int)hauteurFenetre()*0.7;
			virus[j].xdir = 0;
			virus[j].ydir = -1;
			virus[j].width = 128;
			virus[j].height = 128;
			virus[j].life = 100;
		}
		return virus;
	}
}
