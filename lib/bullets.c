#include "bullets.h"

static int bulletsSize;

void cercle(float centreX, float centreY, float rayon){
	const int Pas = 20; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2.*M_PI/Pas;
	for (int index = 0; index < Pas; ++index){
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
	}		
}

Bullet *initBullets(int from, int to){
	
	Bullet tempbul;
	tempbul.x = 0;
	tempbul.y = 0;
	tempbul.width = 10;
	tempbul.height = 10;
	tempbul.del = true;
	tempbul.ally = true;
	tempbul.damage = 0;
	
	bulletsSize = INITIAL_BULLET_DRAW_CAPACITY;

	Bullet *bullets;
	bullets = (Bullet*)malloc(to*sizeof(Bullet));
	for(int i = from; i < to; i++) {
		bullets[i] = tempbul;
	}
	return bullets;
}


Bullet *resize(Bullet *array, int oldSize, int newSize){
	// *bullets = realloc(*bullets, sizeof(Bullet));
	Bullet *newArray;
	
	printf("bulletsSize  before: %d\n", bulletsSize);
	bulletsSize = newSize > oldSize ? oldSize : newSize;
	printf("bulletsSize  after: %d\n", bulletsSize);
	
	newArray = realloc(array, bulletsSize);

//	newArray = malloc(newSize);
	//memset(newArray, 0, newSize);
	//memcpy(newArray, array, bulletsSize);

	//newArray = initBullets(oldSize, newSize);
	free(array);
	
	return newArray;
}


Bullet newBullet(int x, int y, bool isAlly){
	Bullet b;

	//b = malloc(sizeof(Bullet));
	//memset(b, 0, sizeof(Bullet));

	b.x = x;
	b.y = y;
	b.width = 10;
	b.height = 10;
	b.speed = 10;
	b.del = false;
	b.ally = isAlly;
	b.damage = 25;

	return b;
}

bool isCollide(int x, int y, int width, int height, int x2, int y2, int width2, int height2){
	int coinX1 = x-width/2;
	int coinY1 = y-height/2;

	int coinX2 = x-width/2;
	int coinY2 = y+height/2;

	int coinX3 = x+width/2;
	int coinY3 = y+height/2;

	int coinX4 = x+width/2;
	int coinY4 = y-height/2;


	int e2CoinX1 = x2 - width2/2;
	int e2CoinY1 = y2 - height2/2;
	int e2CoinX3 = x2 + width2/2;
	int e2CoinY3 = y2 + height2/2;

	//printf("c1, c2, c3, c4: %d:%d  %d:%d  %d:%d  %d:%d\n", coinX1, coinY1, coinX2, coinY2, coinX3, coinY3, coinX4, coinY4);
	//printf("###########E2: %d:%d  %d:%d \n\n", e2CoinX1, e2CoinY1, e2CoinX3, e2CoinY3);
	if(e2CoinX1 < coinX1 && coinX1 < e2CoinX3 && e2CoinY1 < coinY1 && coinY1 < e2CoinY3)
		return true;
	if(e2CoinX1 < coinX2 && coinX2 < e2CoinX3 && e2CoinY1 < coinY2 && coinY2 < e2CoinY3)
		return true;
	if(e2CoinX1 < coinX3 && coinX3 < e2CoinX3 && e2CoinY1 < coinY3 && coinY3 < e2CoinY3)
		return true;
	if(e2CoinX1 < coinX4 && coinX4 < e2CoinX3 && e2CoinY1 < coinY4 && coinY4 < e2CoinY3)
		return true;

	return false;


}

void checkCollisions(Ship ship, Bullet *bullets, int bSize, Level *levels, int currentLevel){
	for (int j = 0; j < bSize; ++j){
		if (bullets[j].ally){
			for (int i = 0; i < levels[currentLevel].qtVirusPerLvl; ++i){
				if(isCollide(bullets[j].x, bullets[j].y, bullets[j].width, bullets[j].height, levels[currentLevel].virus[i].x, levels[currentLevel].virus[i].y, levels[currentLevel].virus[i].width, levels[currentLevel].virus[i].height)){
					printf("destroyBullets + reduire hp ou meurt\n");
				}
			}
		}
	}


}

void drawBullets(Bullet *bullets, int size){
	for (int i = 0; i < size; i++){
		if(bullets[i].del == false) {
			if(bullets[i].ally) {
				bullets[i].y += bullets[i].speed;
			}
			else {
				bullets[i].y -= bullets[i].speed;
			}
			showBullet(bullets[i].x, bullets[i].y);
		}
	}
}

static void showBullet(int x, int y){
	couleurCourante(150, 0, 50);
	cercle(x, y, 5);
}



int getSize(){
	return bulletsSize;
}

/*
void destroyBullets(void){
	free(bullets);
	bullets = NULL;
}
*/
