#include "ship.h"


Ship initShip(void){
	
	Ship tempShip;
	tempShip.x = largeurFenetre()/2;
	tempShip.y = 0;
	tempShip.xdir = 0;
	tempShip.ydir = 0;
	tempShip.width = 128;
	tempShip.height = 128;
	tempShip.life = 5;
	tempShip.speed = 8;	
	tempShip.score = 0;	
	tempShip.reloadTime = 0;

	return tempShip;
}

void moveShipCollide(Ship *ship){
	if(ship->x+ship->width/2 > largeurFenetre()+20 ){
		ship->x = largeurFenetre()+20-ship->width/2;
	} 
	if(ship->y+ship->height/2 > hauteurFenetre() ){
		ship->y = hauteurFenetre()-ship->height/2;
	} 
	if(ship->x-ship->width/2 < 0 ){
		ship->x = ship->width/2;
	} 
	if(ship->y-ship->height/2 < 0 ){
		ship->y = ship->height/2;
	}
}

void moveShip(Ship *ship){
	ship->x += ship->xdir * ship->speed;
	ship->y += ship->ydir * ship->speed;

	ship->xdir = 0;
	ship->ydir = 0;
}

void showImage(int x, int y, DonneesImageRGB *image){
	if (image != NULL) {
		ecrisImage(x, y, image->largeurImage, image->hauteurImage, image->donneesRGB);
	}
}
