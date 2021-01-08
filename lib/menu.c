int afficheMenuStart (int Hscore, DonneesImageRGB *fond){	
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
	couleurCourante (250, 255, 255);
	epaisseurDeTrait (2);
	afficheChaine (" High Score ", 20, 650, 280);
	
	showMenucore(Hscore);
	//showImage(0, 0, fond);
	

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

void showMenucore(int Hscore)
{
	int HscoreLength = snprintf(NULL, 0, "%d", Hscore);
	char* str = malloc(HscoreLength + 1);
	char Highscore[] = " Hscore ";
	snprintf(str, HscoreLength + 2, "%d", Hscore);

	couleurCourante(50, 50, 150);
	epaisseurDeTrait(3);
	afficheChaine(str, 20, largeurFenetre()*0.025, hauteurFenetre()*0.95);
	free(str);
}

