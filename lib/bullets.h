#define INITIAL_BULLET_DRAW_CAPACITY 12

void cercle(float centreX, float centreY, float rayon);


Bullet *initBullets(int from, int to);
Bullet createBullet();
Bullet newBullet(int x, int y, bool isAlly);

Bullet *copyTab(Bullet *bullets, int x, int y, bool isAlly);
Bullet *removeBullet(Bullet *bullets);
bool isCollide(int x, int y, int width, int height, int x2, int y2, int width2, int height2);
int *checkCollisionsBullet(Ship ship, Bullet *bullets, Ship *virus, int *score);



void drawBullets(Bullet *bullets, DonneesImageRGB *imageally,DonneesImageRGB *imageenemy);
int getSize();
void initSize();
void resetBullets(Bullet *bullets);
