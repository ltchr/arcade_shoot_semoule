#include "score.h"

void showScore(int score){
	int scoreLength = snprintf(NULL, 0, "%d", score);
	char* str = malloc(scoreLength + 1);
	snprintf(str, scoreLength + 1, "%d", score);

	couleurCourante(250, 250, 150);
	epaisseurDeTrait(3);
	afficheChaine(str, 20, largeurFenetre()*0.025, hauteurFenetre()*0.95);
	free(str);
}

void showLevel(int currentLevel){
	char lvlName[] = "niveau: ";
	int levelLength = snprintf(NULL, 0, "%d", currentLevel);
	char* str = malloc(levelLength + sizeof(lvlName));
	//snprintf(str, levelLength + 1, "%d", currentLevel);
	snprintf(str, sizeof(str)+4, "%s%d", lvlName, currentLevel);

	couleurCourante(250, 250, 250);
	epaisseurDeTrait(2);
	afficheChaine(str, 20, largeurFenetre()*0.82, hauteurFenetre()*0.025);
	free(str);
}

void showLives(int lives){
	char strAdd[] = "Vies: ";
	int livesLength = snprintf(NULL, 0, "%d", lives);
	char* str = malloc(livesLength + sizeof(strAdd));
	sprintf(str, "%s%d", strAdd, lives);

	couleurCourante (250, 255, 255);
	epaisseurDeTrait(2);
	afficheChaine(str, 20, largeurFenetre()*0.025, hauteurFenetre()*0.85);
	free(str);
}


/*
// Facultativ
void showEndLeveLScore(int currentLevel, int score){
	sautDeLigne();
}*/

/*
// TODO 
// generaliser l affiche d un texte a une position
void showGui(int x, int y, int data, char* comment, int commentLength){
}
*/