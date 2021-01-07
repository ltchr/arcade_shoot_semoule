#define INITIAL_BULLET_DRAW_CAPACITY 12

void cercle(float centreX, float centreY, float rayon);


Bullet *initBullets(int from, int to);
Bullet *resize(Bullet *array, int oldSize, int newSize);
Bullet *checkCollisions(Ship ship, Bullet *bullets, Ship *virus);
bool isCollide(int x, int y, int width, int height, int x2, int y2, int width2, int height2);
Bullet newBullet(int x, int y, bool isAlly);
Bullet createBullet();


void drawBullets(Bullet *bullets, DonneesImageRGB *image);
static void showBullet(int x, int y); // show bullet at a x y
void destroyBullets(void);
int getSize();
