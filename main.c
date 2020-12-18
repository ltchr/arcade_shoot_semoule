/*	
* 
*/

#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // cos
#include "lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "lib/ESLib.h" // Pour utiliser valeurAleatoire()

//#include "joueur.h"
#include "lib/def.h"
#include "lib/struct.h"

void gestionEvenement(EvenementGfx evenement);
void cercle(float centreX, float centreY, float rayon);
void showScore();
void clear(Level* levels); // clear the malloc of levels
void showShip(int x, int y, int w, int h); 
void moveShip(Ship *ship); // move the ship to a direction
void moveBullet(Bullet** bullets); 
void resize(Bullet** bullets); // increase the bullets size array
void newBullet(Bullet** bullets, Ship ship); // create a bullet where the ship is
void showBullet(int x, int y); // show bullet at a x y

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

void clear(Level* levels){
	free(levels);
	levels = NULL;
}

void newBullet(Bullet** bullets, Ship ship){
	int len = (sizeof(bullets)/sizeof(bullets[0]));
	bullets[len]->x = ship.x;
	bullets[len]->y = ship.y;
	bullets[len]->del = false;
	bullets[len]->damage = 25;
}

void moveShip(Ship *ship){
	ship->x += ship->xdir * ship->speed;
	ship->y += ship->ydir * ship->speed;

	ship->xdir = 0;
	ship->ydir = 0;
}

void moveBullet(Bullet** bullets){

}

void showScore(int score){
	//printf("score %d\n", score);
}

void resize(Bullet** bullets){
    *bullets = realloc(*bullets, sizeof(Bullet));
}

void showBullet(int x, int y){
	couleurCourante(150, 0, 50);
	cercle(x, y, 10);
}

void showShip(int x, int y, int w, int h){
	couleurCourante(255, 160, 160);
	rectangle(x, y, x+w, y+h);
}

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);

	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);
	
	lanceBoucleEvenements();
	
	return 0;
}
// La fonction de gestion des evenements, appelee automatiquement par le systeme
// des qu'un evenement survient
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static bool gameover = false;
	static int score;
	static int Hscore;
	
	static Ship ship; 
	
	int qtLevel = 2;
	static int currentLevel = 1;
	static Level *levels = NULL;
	if (levels == NULL){
		levels = (Level*)malloc(qtLevel*sizeof(Level));
	}
	static Bullet *bullets = NULL;
	if (bullets == NULL){
		bullets = (Bullet*)malloc(sizeof(Bullet));
	}

	switch (evenement)
	{
		case Initialisation:
			score = 0;
			Hscore = 0;

			//Ship init
			ship.x = largeurFenetre()/2;
			ship.y = 0;
			ship.xdir = 0;
			ship.ydir = 0;
			ship.width = 20;
			ship.height = 30;
			ship.life = 100;
			ship.speed = 3;
			// Init levels
			for (int i = 0; i < qtLevel; ++i){
				levels[i].qtVirusPerLvl = (i + 1)*3;
				levels[i].hasBoss = false;
				levels[i].allDead = false;
				for (int j = 0; j < levels[i].qtVirusPerLvl; ++j){
					levels[i].virus[j].x = j*100;
					levels[i].virus[j].y = (int)hauteurFenetre()*0.9;
					levels[i].virus[j].xdir = 0;
					levels[i].virus[j].ydir = -1;
					levels[i].virus[j].width = 20;
					levels[i].virus[j].height = 20;
					levels[i].virus[j].life = 100;
				}
			}


/*			PosXY pos;
			pos.x = largeurFenetre()/2;
			pos.y = hauteurFenetre()/2;
				
			Joueur* joueur = new_joueur(pos, 10.0f, 10.0f);
			joueur->move((Entite*)joueur, pos, 5.0f, 5.0f);
*/


			demandeTemporisation(20);
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:			
			effaceFenetre (255, 255, 255);
			if (!gameover && !levels[currentLevel].allDead){
				int len = sizeof(bullets)/sizeof(bullets[0]);
				//printf("*****len %d\n", len);
				for (int i = 0; i < len; ++i){
					showBullet(largeurFenetre()/2, hauteurFenetre()/2);
					//showBullet(ship.x, ship.y);
				}
				for (int i = 0; i < levels[currentLevel].qtVirusPerLvl; ++i){
					showShip(levels[currentLevel].virus[i].x, levels[currentLevel].virus[i].y, levels[currentLevel].virus[i].width, levels[currentLevel].virus[i].height);
				}
				showShip(ship.x, ship.y, ship.width, ship.height);			
				moveShip(&ship);
				showScore(score);
			}else{

				if(score > Hscore){
					Hscore = score;
				}
				currentLevel = 1;
				clear(levels);
			}

			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
			if(caractereClavier() == 'z' || caractereClavier() == 'Z'){
				ship.ydir += 1;
			}
			if(caractereClavier() == 's' || caractereClavier() == 'S'){
				ship.ydir -= 1;
			}
			if(caractereClavier() == 'd' || caractereClavier() == 'D'){
				ship.xdir += 1;
			}
			if(caractereClavier() == 'q' || caractereClavier() == 'Q'){
				ship.xdir -= 1;
			}
			if(caractereClavier() == ' '){
				//resize(&bullets);
				//newBullet(&bullets, ship);
			}
			switch (caractereClavier())
			{
				/*
				case 'Z':
				case 'z':
					ship.ydir = 1;
				break;
				case 'S':
				case 's':
					ship.ydir = -1;
				break;
				case 'Q':
				case 'q':
					ship.xdir = -1;
				break;
				case 'D':
				case 'd':
					ship.xdir = 1;
				break;
*/
				case 'P':
				case 'p':
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran;
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 100 millisecondes (lent)
					demandeTemporisation(100);
					break;

				case 'W':
				case 'w':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			if(toucheClavier() == ToucheFlecheHaut){
				ship.ydir += 1;
			}
			if(toucheClavier() == ToucheFlecheBas){
				ship.ydir -= 1;
			}
			if(toucheClavier() == ToucheFlecheDroite){
				ship.xdir += 1;
			}
			if(toucheClavier() == ToucheFlecheGauche){
				ship.xdir -= 1;
			}

			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}

