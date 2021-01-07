#include "score.h"

void showScore(int score){
	int scoreLength = snprintf(NULL, 0, "%d", score);
	char* str = malloc(scoreLength + 1);
	snprintf(str, scoreLength + 1, "%d", score);

	couleurCourante(50, 50, 150);
	epaisseurDeTrait(3);
	afficheChaine(str, 20, largeurFenetre()*0.025, hauteurFenetre()*0.95);
	free(str);
}

void showLevel(int currentLevel){
	char lvlName[] = "niveau: ";
	int levelLength = snprintf(NULL, 0, "%d", currentLevel);
	char* str = malloc(levelLength + sizeof(lvlName));
	//snprintf(str, levelLength + 1, "%d", currentLevel);
	snprintf(str, sizeof(str)+3, "%s%d", lvlName, currentLevel);

	couleurCourante(80, 80, 100);
	epaisseurDeTrait(2);
	afficheChaine(str, 20, largeurFenetre()*0.82, hauteurFenetre()*0.025);
	free(str);
}

void showEndLeveLScore(int currentLevel, int score){
	sautDeLigne();
}