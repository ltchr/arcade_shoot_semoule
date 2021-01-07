#include "virus.h"

static int qtEnemy = 0;

bool checkEnemyLeft(Ship *virus) {
	int livingEnemy = 0;
	for(int j = 0; j < getVirusQt(); ++j) {
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

// getMaxVirusPerLevel
int getVirusQt() {
	return qtEnemy;
}

Ship *initVirus(int level){
	qtEnemy = level*2;
	Ship *virus;
	virus = (Ship*)malloc(getVirusQt()*sizeof(Ship));
	if (virus == NULL){
		exit(EXIT_FAILURE);
	}
	for (int j = 0; j < getVirusQt(); ++j){
		virus[j].x = j*150 + 32;
		virus[j].y = (int)hauteurFenetre()*0.7;
		virus[j].xdir = 0;
		virus[j].ydir = -1;
		virus[j].width = 64;
		virus[j].height = 64;
		virus[j].life = 100;
	}
	return virus;
}
