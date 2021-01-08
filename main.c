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
#include "menu.c"

void gestionEvenement(EvenementGfx evenement);
void clear(); // clear the malloc of levels

// Etats touches mouvement
static int tZ = 0;
static int tQ = 0;
static int tS = 0;
static int tD = 0;

//static bool pleinEcran = false;
static bool gameover;
static int score;
static int Hscore;

static Ship ship; 

static int currentLevel;

static Ship *virus;

static Bullet *bullets;

static bool isMenu;
static int choixMenu;

static unsigned int timer = 0;

static DonneesImageRGB *spaceShipSprite = NULL;
static DonneesImageRGB *virusSprite = NULL;
static DonneesImageRGB *virusBullet = NULL;
static DonneesImageRGB *shipBullet = NULL;
static DonneesImageRGB *background = NULL;
static DonneesImageRGB *fondMenu = NULL;

void clear(){
	libereDonneesImageRGB(&spaceShipSprite);
	libereDonneesImageRGB(&virusSprite);
	libereDonneesImageRGB(&virusBullet);
	libereDonneesImageRGB(&shipBullet);
	libereDonneesImageRGB(&background);
	libereDonneesImageRGB(&fondMenu);
}

void newGame(){
	currentLevel = 100;
	choixMenu = -1;
	isMenu = true;
	gameover = false;
	initSize();

	ship = initShip();
	virus = initVirus(currentLevel);
	bullets = initBullets(0, INITIAL_BULLET_DRAW_CAPACITY);

	timer = (int)tempsReel();
}

void endLevel(){
	free(bullets);
	free(virus);
}

void endGame(){
	if(score > Hscore){
		Hscore = score;
	}
	currentLevel = 1;

	score = 0;
	endLevel();
}

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);

	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);
	
	lanceBoucleEvenements();
	
	return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
	switch (evenement)
	{
		case Initialisation:
			score = 0;
			Hscore = 0;

			spaceShipSprite = lisBMPRGB("../img/Main_character.bmp");
			virusSprite = lisBMPRGB("../img/virus.bmp");
			virusBullet = lisBMPRGB("../img/virusbullet.bmp");
			shipBullet = lisBMPRGB("../img/playerbullet.bmp");
			background = lisBMPRGB("../img/background.bmp");
			fondMenu = lisBMPRGB("../img/fond.bmp");

			newGame();
			
			demandeTemporisation(FPS);
			break;
		
		case Temporisation:
			if (!gameover && !isMenu){
				ship.ydir += (tZ+tS);
				ship.xdir += (tD+tQ);
				if(!checkEnemyLeft(virus)){
					bullets = initBullets(0, INITIAL_BULLET_DRAW_CAPACITY);
					initSize();


		            timer = (int)tempsReel();
				 	currentLevel++;
		            virus = initVirus(currentLevel);
		            while (tempsReel()-timer<2){
		            	//draw score of the lvl
		            }
		        	ship.x = largeurFenetre()/2;
		        	ship.y = 0;
				}

				for (int i = 0; i < getVirusQt(); ++i){
					if (virus[i].life>0){
						
						moveVirus(&virus[i]);
						if (virus[i].reloadTime > valeurAleatoire()*10){
							bullets = copyTab(bullets, virus[i].x, virus[i].y-virus[i].height/2, false);
							timer = tempsReel();
							virus[i].reloadTime = 0;									
						}else{
							virus[i].reloadTime = (int)tempsReel()-timer;
						}
					}
				}
				int dmg;
				if(dmg = checkCollisionsBullet(ship, bullets, virus, &score) > 0) {
					ship.life -= dmg;
					if (ship.life<=0){
						gameover = true;
					}
				}

				moveShip(&ship);
				moveShipCollide(&ship);
			}
			rafraichisFenetre();
			break;
			
		case Affichage:

			//Gestion direction mouvement



			if (isMenu){
				choixMenu = afficheMenuStart(Hscore, background);
				if (choixMenu != -1){
					isMenu = false;
				}
			}
			switch(choixMenu){
				case 1:
					showImage(0, 0, background);
					if (!gameover && !isMenu){
						showScore(score);

						for (int i = 0; i < getVirusQt(); ++i){
							if(virus[i].life>0) {
								showImage(virus[i].x - virus[i].width/2, virus[i].y - virus[i].height/2, virusSprite);
							}
						}
						drawBullets(bullets, shipBullet, virusBullet);
						showImage(ship.x-ship.width/2, ship.y-ship.height/2, spaceShipSprite);	
						showLevel(currentLevel);
					}
					else {
						isMenu = true;
						endGame();
						//choixMenu = -1;
						newGame();
					}
					break;

				case 2:
				break;

				case 3:
					clear();
				break;

				default: 
					isMenu = true;
					break;
			}
		
			break;
			
		case Clavier:
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
						bullets = copyTab(bullets, ship.x +5, ship.y+ship.height/2, true);

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
			break;
			
		case ClavierSpecial:
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
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}

