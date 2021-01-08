
void showMenucore(int Hscore)
{
	if (Hscore>0){
		char strAdd[] = "Your high score ";
		char strIs[] = "is: ";

		int HscoreLength = snprintf(NULL, 0, "%d", Hscore);
		char* str = malloc(HscoreLength + sizeof(strAdd) + sizeof(strIs));
		sprintf(str, "%s%s%d", strAdd, strIs, Hscore);

		couleurCourante (250, 255, 255);
		afficheChaine(str, 20, 600, 200);
		free(str);
	}
}

int afficheMenuStart (int Hscore){	
	int valRet = 0;

	char recclavier; 
	//couleurCourante (0, 255, 0); 
	//rectangle(255, 255, 600, 400);

	//affichage du Menu	
	couleurCourante (250, 255, 255);
	epaisseurDeTrait (2);
	afficheChaine ("Menu : ", 20, 696, 370);
	
	//affichage du titre
	couleurCourante (255, 120, 120);
	epaisseurDeTrait (4);
	afficheChaine (" SHOOT VIRUS SIMULATOR ", 50, 348, 450);
	
	//affichage fonction start
	couleurCourante (250, 255, 255);
	epaisseurDeTrait (2);
	afficheChaine ("Start : Press < s >", 20, 610, 320);
	
	//affichage meilleurScore
	showMenucore(Hscore);

	

	recclavier=caractereClavier();
	if(recclavier == 's' || recclavier == 'S'){ 
		printf("le caractere est %c \n", recclavier);
		printf("lancement du jeu \n");
		effaceFenetre (255, 255, 255);
		printf("choix 1\n");

		valRet = 1;
	}
	else if(recclavier == 'a' || recclavier == 'A'){ 
		printf("choix 2\n");
		valRet = 2;
	}
	return valRet;
}


/*
char* initScoreName(char *chaineReponse, int taille){
	chaineReponse = (char*)malloc(sizeof(char)*taille);
	for (int i = 0; i < taille; ++i){
		chaineReponse[i] = '\0';
	}
	return chaineReponse;
}


void afficher(char *tab, int taille){
	printf("taille est %d\nles valeurs sont \n", taille);
	for (int i = 0; i < taille; i++){
		printf("[%d]: %c ",i, *(tab+i));
	}
	printf("\n");
}

void typeScoreName(char *chaineReponse, int *index, char value, int taille){
	if(*index == taille){
		taille += 10;
		chaineReponse = (char *)realloc(chaineReponse, sizeof(char) * taille);
	}
	chaineReponse[*index] = value;
	*index = *index + 1;
	printf("saisie de: %c a la case %ls et taille %d\n", value, index, taille);
	for (int i = 0; i < *index; ++i){
		ecrisCaractere(chaineReponse[*index]);
	}
	printf("\n");
	afficher(chaineReponse, taille);
}

*/