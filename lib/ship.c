#include "ship.h"


Ship initShip(void){
	
	Ship tempShip;
	tempShip.x = largeurFenetre()/2;
	tempShip.y = 0;
	tempShip.xdir = 0;
	tempShip.ydir = 0;
	tempShip.width = 20;
	tempShip.height = 30;
	tempShip.life = 100;
	tempShip.speed = 3;	

	return tempShip;
}

void moveShip(Ship *ship){
	ship->x += ship->xdir * ship->speed;
	ship->y += ship->ydir * ship->speed;

	ship->xdir = 0;
	ship->ydir = 0;
}

void showShip(int x, int y, DonneesImageRGB *image){
	if (image != NULL) {
		ecrisImage(x, y, image->largeurImage, image->hauteurImage, image->donneesRGB);
	}
	//couleurCourante(255, 160, 160);
	//rectangle(x, y, x+w, y+h);
}
