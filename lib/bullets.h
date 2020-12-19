#define INITIAL_BULLET_DRAW_CAPACITY 32

void cercle(float centreX, float centreY, float rayon);


void initBullets(void);
void *resize(void *array, int oldSize, int newSize);
void checkCollisions(/*Bullet *b*/);
void drawBullets();
void destroyBullets(void);
void resizeDrawList(void);
Bullet *newBullet(int x, int y);

void showBullet(int x, int y); // show bullet at a x y