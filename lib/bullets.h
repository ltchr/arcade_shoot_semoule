#define INITIAL_BULLET_DRAW_CAPACITY 128

void cercle(float centreX, float centreY, float rayon);


Bullet *initBullets(void);
void *resize(void *array, int oldSize, int newSize);
void checkCollisions(/*Bullet *b*/);
void drawBullets();
void destroyBullets(void);
void resizeDrawList(void);
Bullet newBullet(int x, int y, bool isAlly);

void showBullet(int x, int y); // show bullet at a x y
