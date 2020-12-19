#include "bullets.h"

static Bullet **bullets;
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


void initBullets(void){
	drawCapacity = INITIAL_BULLET_DRAW_CAPACITY;
	bullets = (Bullet*)malloc(drawCapacity*sizeof(Bullet));
	memset(bullets, 0, sizeof(Bullet*) * drawCapacity);
}

void *resize(void *array, int oldSize, int newSize){
	//*bullets = realloc(*bullets, sizeof(Bullet));
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

Bullet *newBullet(int x, int y){
	Bullet *b;

	b = malloc(sizeof(Bullet));
	memset(b, 0, sizeof(Bullet));

	b->x = x;
	b->y = y;
	b->del = false;
	b->damage = 25;

	return b;
}

//void moveBullet(Bullet** bullets); 


void checkCollisions(/*Bullet *b*/){

}

void drawBullets(void){
	int i;
	Bullet *b;
	//int len = sizeof(bullets)/sizeof(bullets[0]);
	//printf("*****len %d\n", len);
	for (i = 0, b = bullets[i]; b != NULL; b = bullets[++i]){
		showBullet(largeurFenetre()/2, hauteurFenetre()/2);
		//showBullet(ship.x, ship.y);
	}
}


void showBullet(int x, int y){
	couleurCourante(150, 0, 50);
	cercle(x, y, 10);
}

void destroyBullets(void){
	free(bullets);
	bullets = NULL;
}