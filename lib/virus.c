#include "virus.h"

static int qtEnemy = 0;

// getMaxVirusPerLevel
int getVirusQt(){
	return qtEnemy;
}

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

int generatePosX(){
	return (int)(320 + (valeurAleatoire()*(largeurFenetre()-720)));
}

int generatePosY(int level){
	return (int)(valeurAleatoire()*(level*80));
}

Ship *initVirus(int level){
	qtEnemy = level*2;
	Ship *virus;
	virus = (Ship*)malloc(getVirusQt()*sizeof(Ship));
	if (virus == NULL){
		exit(EXIT_FAILURE);
	}
	for (int j = 0; j < getVirusQt(); ++j){
		virus[j].width = 64;
		virus[j].height = 64;
		virus[j].x = generatePosX();
		virus[j].y = (int)hauteurFenetre()+virus[j].height + generatePosY(level);
		int randomval = valeurAleatoire();
		if(randomval > 0.5) {
			virus[j].xdir = 10;
		}
		else {
			virus[j].xdir = -10;
		}
		virus[j].ydir = -1;
		virus[j].life = 100;
		virus[j].speed = 1;
		virus[j].score = 2;
		virus[j].reloadTime = 0;
	}
	return virus;
}

void moveVirusCollide(Ship *ship){
	if(ship->x+ship->width/2 > largeurFenetre()-320 ){
		ship->xdir = -10;
	} 
	if(ship->x-ship->width/2 < 320 ){
		ship->xdir = 10;
	} 
	if(ship->y-ship->height/2 < 0 ){
		ship->life = 0;
	}
}

void moveVirus(Ship *ship){
	ship->x += ship->xdir * ship->speed;
	ship->y += ship->ydir * ship->speed;
	moveVirusCollide(ship);
}
