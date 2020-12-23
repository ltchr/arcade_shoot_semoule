#include "bullets.h"

//static Bullet *bullets;
static int drawCapacity;


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


Bullet *initBullets(void){
	
	Bullet tempbul;
	tempbul.x = 0;
	tempbul.y = 0;
	tempbul.del = true;
	tempbul.ally = true;
	tempbul.damage = 0;
	
	Bullet *bullets;
	drawCapacity = INITIAL_BULLET_DRAW_CAPACITY;
	bullets = (Bullet*)malloc(drawCapacity*sizeof(Bullet));
	for(int i = 0; i < INITIAL_BULLET_DRAW_CAPACITY; i++) {
		bullets[i] = tempbul;
	}
	return bullets;
}
/*
void *resize(void *array, int oldSize, int newSize){
	// *bullets = realloc(*bullets, sizeof(Bullet));
	void **newArray;
	int copySize;
	copySize = newSize > oldSize ? oldSize : newSize;

	newArray = malloc(newSize);
	memset(newArray, 0, newSize);
	memcpy(newArray, array, copySize);
	free(array);
	return newArray;
}

void resizeDrawList(void){
	int n;
	n = drawCapacity + INITIAL_BULLET_DRAW_CAPACITY;
	bullets = resize(bullets, sizeof(Bullet*) * drawCapacity, sizeof(Bullet*) * n);
	printf("## Resize bullets capacity %d -> %d\n", drawCapacity, n);
	drawCapacity = n;
}
*/
Bullet newBullet(int x, int y, bool isAlly){
	Bullet b;

	//b = malloc(sizeof(Bullet));
	//memset(b, 0, sizeof(Bullet));

	b.x = x;
	b.y = y;
	b.del = false;
	b.ally = isAlly;
	b.damage = 25;

	return b;
}

void moveBullet(Bullet *bullets) {
	int i;
	
	for (i = 0; i < INITIAL_BULLET_DRAW_CAPACITY; i++){
		if(bullets[i].del == false) {
			if(bullets[i].ally) {
				bullets[i].y += 10;
			}
			else {
				bullets[i].y -= 10;
			}
		}
	}
}


void checkCollisions(/*Bullet *bullets*/){

}

void drawBullets(Bullet *bullets){
	int i;
	
	for (i = 0; i < INITIAL_BULLET_DRAW_CAPACITY; i++){
		if(bullets[i].del == false) {
			if(bullets[i].ally) {
				bullets[i].y += 10;
			}
			else {
				bullets[i].y -= 10;
			}
			showBullet(bullets[i].x, bullets[i].y);
		}
	}
}


void showBullet(int x, int y){
	couleurCourante(150, 0, 50);
	cercle(x, y, 5);
}
/*
void destroyBullets(void){
	free(bullets);
	bullets = NULL;
}
*/
