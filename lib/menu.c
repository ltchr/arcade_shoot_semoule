int afficheMenuStart (){	
	int valRet = 0;

	char recclavier; 
	couleurCourante (0, 0, 55);
	rectangle(255, 255, 600, 400);
		
	couleurCourante (250, 255, 255);
	epaisseurDeTrait (2);
	afficheChaine ("Menu : ", 20, 400, 370);
	
	couleurCourante (0, 255, 255);
	epaisseurDeTrait (2);
	afficheChaine ("- Start : Press < s >", 13, 260, 340);

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
