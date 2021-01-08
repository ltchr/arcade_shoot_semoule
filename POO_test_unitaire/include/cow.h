#ifndef COW_H
#define COW_H
#include "animal.h"

typedef struct COW_STRUCT
{
	Animal base;
	void* (*speak)(Animal* animal);
} Cow;

Cow* new_cow();
#endif
