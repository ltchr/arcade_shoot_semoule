/*static int currentLevel = 1;
static int qtEnnemyPerLvl = 1;

Level initLevel(){
	level.qtVirusPerLvl = 3;
	level.hasBoss = false;
	level.allDead = false;
	for (int j = 0; j < level.qtVirusPerLvl; ++j){
		level.virus[j].x = j*150;
		level.virus[j].y = (int)hauteurFenetre()*0.7;
		level.virus[j].xdir = 0;
		level.virus[j].ydir = -1;
		level.virus[j].width = 128;
		level.virus[j].height = 128;
		level.virus[j].life = 100;
	}
}

bool nextLevel(Level level){
	if (level.allDead){
		currentLevel++;
	}
}


int getLevel(){
	return currentLevel;
}*/