#include <stdbool.h>

typedef struct
{
	float x;
	float y;
} PointF;

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
	int xdir;
	int ydir;
	int del;
	int damage;

} Bullet;
/*
struct Weapon
{
	int type;
	int ammo;
	int maxAmmo;
	int x;
	int y;
};

struct Entity
{
	int type;
	char name[MAX_NAME_LENGTH];
	char defName[MAX_NAME_LENGTH];
	char groupName[MAX_NAME_LENGTH];
	char *description;
	int active;
	int spawned;
	int id;
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int alive;
	//Entity *owner;
};

*/
