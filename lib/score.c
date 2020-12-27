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