#include <stdbool.h>

typedef struct SHIP_STRUCT
{
	int x;
	int y;
	int xdir;
	int ydir;
	int width;
	int height;
	int life;
	int speed;
	int score;
	float reloadTime;
} Ship;

typedef struct LEVEL_STRUCT
{
	int qtVirusPerLvl;
	bool hasBoss;
	bool allDead;
	Ship virus[255];
}Level;

typedef struct BULLET_STRUCT
{
	//int type;
	int x;
	int y;
	int width;
	int height;
	int speed;
	bool del;
	bool ally;
	int damage;

} Bullet;
