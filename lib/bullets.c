#include "bullets.h"

static int bulletsSize = INITIAL_BULLET_DRAW_CAPACITY;

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
	Bullet *bullets;
	bullets = (Bullet*)malloc(to*sizeof(Bullet));
	for(int i = from; i < to; i++) {
		bullets[i] = createBullet();
	}

	return bullets;
}

Bullet createBullet(){
	Bullet tempbul;

	tempbul.x = 0;
	tempbul.y = 0;
	tempbul.width = 10;
	tempbul.height = 10;
	tempbul.del = true;
	tempbul.ally = true;
	tempbul.damage = 25;

	return tempbul;

}

Bullet newBullet(int x, int y, bool isAlly){
	Bullet b;

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


/*
Bullet *resize(Bullet *array, int oldSize, int newSize){
	//Bullet *newArray;
	
	printf("bulletsSize : %d ; %d ; %d ; %d\n", bulletsSize, oldSize, newSize, getSize());

	if (newSize > getSize()){
		oldSize = bulletsSize;
		bulletsSize = newSize;
		printf("bulletsSize : %d ; %d ; %d ; %d\n", bulletsSize, oldSize, newSize, getSize());
		array = realloc(array, bulletsSize * sizeof(Bullet));
		//array = initBullets(oldSize, newSize);
	}

	//bulletsSize = newSize > oldSize ? newSize : oldSize;

	
	//newArray = realloc(array, bulletsSize);
	// newArray = malloc(newSize);
	// memset(newArray, 0, newSize);
	// memcpy(newArray, array, bulletsSize);

	// newArray = initBullets(oldSize, newSize);
	// free(array);
	
	// return newArray;
	return array;
}*/


Bullet *copyTab(Bullet *bullets, int x, int y, bool isAlly){
	Bullet *newArray = (Bullet*)malloc((getSize()+1)*sizeof(Bullet));

	//memcpy(newArray, bullets, getSize());
	for(int cptBullets = 0; cptBullets < getSize(); cptBullets++) {
		newArray[cptBullets] = bullets[cptBullets];
	}
	newArray[getSize()] = newBullet(x, y, isAlly);
	bulletsSize++;
	return newArray;
}

Bullet *removeBullet(Bullet *bullets){
	Bullet *newArray = (Bullet*)malloc((getSize())*sizeof(Bullet));
	int newCptBullets=0;

	printf("getSize %d\n", getSize());
	//memcpy(newArray, bullets, getSize());
	for(int cptBullets = 0; cptBullets < getSize(); cptBullets++) {
		if(!bullets[cptBullets].del){
			newArray[newCptBullets] = bullets[cptBullets];
			newCptBullets++;
		}
	}
	return newArray;
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

Bullet *checkCollisions(Ship ship, Bullet *bullets, Ship *virus){
	Bullet *newBullets = NULL;
	newBullets = bullets;

	for (int j = 0; j < getSize(); ++j){
		if (bullets[j].ally){
			for (int i = 0; i < enemyNumbers(1); ++i){
				if(!bullets[j].del && isCollide(bullets[j].x, bullets[j].y, bullets[j].width, bullets[j].height, virus[i].x, virus[i].y, virus[i].width, virus[i].height)){
					virus[i].life -= bullets[j].damage;
					bullets[j].del = true;
					newBullets = removeBullet(bullets);
				}
			}
		}
	}
	return newBullets;
}


// nombre de bullets à false
// copie de tableau sur un nouveau tableau sans les false

void drawBullets(Bullet *bullets, int size){
	for (int i = 0; i < size; i++){
		if(!bullets[i].del) {
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
