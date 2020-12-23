/*	
* 
*/


#include "lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "lib/ESLib.h" // Pour utiliser valeurAleatoire()

//#include "joueur.h"
#include "common.h"
#include "bullets.c"

void gestionEvenement(EvenementGfx evenement);
void showScore();
void clear(Level* levels); // clear the malloc of levels
void showShip(int x, int y, int w, int h); 
void moveShip(Ship *ship); // move the ship to a direction

//Etats touches mouvement
int tZ = 0;
int tQ = 0;
int tS = 0;
int tD = 0;

static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
static bool gameover = false;
static int score;
static int Hscore;

static Ship ship; 

int qtLevel = 2;
static int currentLevel = 1;
static Level *levels = NULL;

static Bullet *bullets;

void clear(Level* levels){
	free(levels);
	levels = NULL;
}



void moveShip(Ship *ship){
	ship->x += ship->xdir * ship->speed;
	ship->y += ship->ydir * ship->speed;

	ship->xdir = 0;
	ship->ydir = 0;
}

void showScore(/*int score*/){
	//printf("score %d\n", score);
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

	if (levels == NULL){
		levels = (Level*)malloc(qtLevel*sizeof(Level));
	}
	/*static Bullet *bullets = NULL;
	if (bullets == NULL){
		bullets = (Bullet*)malloc(20*sizeof(Bullet));
	}
	if (bullets == NULL || levels == NULL){
		printf("malloc null\n");
		exit(EXIT_FAILURE);
	}
	*/

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
			bullets = initBullets();

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
		
			//Gestion direction mouvement
			ship.ydir += (tZ+tS);
			ship.xdir += (tD+tQ);
			
		
			effaceFenetre (255, 255, 255);
			if (!gameover && !levels[currentLevel].allDead){
				moveBullet(bullets);
				drawBullets(bullets);
				for (int i = 0; i < levels[currentLevel].qtVirusPerLvl; ++i){
					showShip(levels[currentLevel].virus[i].x, levels[currentLevel].virus[i].y, levels[currentLevel].virus[i].width, levels[currentLevel].virus[i].height);
				}
				moveShip(&ship);
				showShip(ship.x, ship.y, ship.width, ship.height);			
				
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
			printf("Etat: %d\n",etatCharacterClavier());
			printf("Touche: %d\n",caractereClavier());
			
			if(etatCharacterClavier()) {
				switch(caractereClavier()) {
					case 'z':
					case 'Z':
						tZ = 1; break;
						
					case 'q':
					case 'Q':
						tQ = -1; break;
						
					case 's':
					case 'S':
						tS = -1; break;
						
					case 'd':
					case 'D':
						tD = 1; break;
						
					case ' ':
						
						//newBullet(ship.x, ship.y)
						;
						int i = 0;
						for(; i < INITIAL_BULLET_DRAW_CAPACITY; i++) {
							if(bullets[i].del == true) {
								break;
							}
						}
						bullets[i] = newBullet(ship.x, ship.y, true);
						
						
						break;
				}
			}
			else {
				switch(caractereClavier()) {
					case 'z':
					case 'Z':
						tZ = 0; 
						break;
						
					case 'q':
					case 'Q':
						tQ = 0; 
						break;
						
					case 's':
					case 'S':
						tS = 0; 
						break;
						
					case 'd':
					case 'D':
						tD = 0; 
						break;
				}
			}
			
			/*

			if(caractereClavier() == ' '){

			//	newBullet(&bullets, ship);
			}
			
			switch (caractereClavier())
			{
				
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
			*/
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

