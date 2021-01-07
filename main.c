/*	
* 
*/


#include "lib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "lib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "lib/ESLib.h" // Pour utiliser valeurAleatoire()

//#include "joueur.h"
#include "common.h"
#include "bullets.c"
#include "ship.c"
#include "score.c"
#include "virus.c"

void gestionEvenement(EvenementGfx evenement);
void clear(Level* levels); // clear the malloc of levels

// Etats touches mouvement
static int tZ = 0;
static int tQ = 0;
static int tS = 0;
static int tD = 0;

//static bool pleinEcran = false;
static bool gameover = false;
static int score;
static int Hscore;

static Ship ship; 

static int qtLevel = 2;
static int currentLevel = 1;
static Level *levels = NULL;

static Ship *virus;

static Bullet *bullets;

static DonneesImageRGB *spaceShipSprite = NULL;
static DonneesImageRGB *virusSprite = NULL;

void clear(Level* levels){
	free(levels);
	levels = NULL;
	libereDonneesImageRGB(&spaceShipSprite);
	libereDonneesImageRGB(&virusSprite);
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

	switch (evenement)
	{
		case Initialisation:
			score = 0;
			Hscore = 0;

		//	spaceShipSprite = lisBMPRGB("../img/ISEN.bmp");
			spaceShipSprite = lisBMPRGB("../img/Main_character.bmp");
			virusSprite = lisBMPRGB("../img/virus.bmp");

			ship = initShip();
			// Init virus
			virus = initVirus(1);
			
			
			bullets = initBullets(0, INITIAL_BULLET_DRAW_CAPACITY);

			demandeTemporisation(FPS);
			break;
		
		case Temporisation:
			rafraichisFenetre();
			break;
			
		case Affichage:
			effaceFenetre (255, 255, 255);
		
			//Gestion direction mouvement
			ship.ydir += (tZ+tS);
			ship.xdir += (tD+tQ);
			
		
			if (!gameover && checkEnemyLeft(virus)){
				checkCollisions(ship, bullets, getSize(), virus);
				drawBullets(bullets, getSize());
				for (int i = 0; i < enemyNumbers(1); ++i){
					showShip(virus[i].x - virus[i].width/2, virus[i].y - virus[i].height/2, virusSprite);
				}
				moveShip(&ship);
				moveShipCollide(&ship);
				showShip(ship.x-ship.width/2, ship.y-ship.height/2, spaceShipSprite);	
				
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
			//printf("Etat: %d\n",etatCharacterClavier());
			//printf("Touche: %d\n",caractereClavier());
			
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
						;
						bullets = copyTab(bullets);

						int i = 0;
						for(; i < getSize(); i++) {
							if(bullets[i].del == true) {
								bullets = removeBullet(bullets);
								break;
							}
						}
						bullets[i] = newBullet(ship.x, ship.y+ship.height/2, true);

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

