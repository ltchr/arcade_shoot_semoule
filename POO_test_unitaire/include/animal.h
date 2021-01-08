#ifndef ANIMAL_H
#define ANIMAL_H 
typedef struct ANIMAL_STRUCT
{
	char* speech;
	void* (*speak)(struct ANIMAL_STRUCT* self);
} Animal;

Animal* animal_constructor(Animal* animal, char* speech);

void animal_speak(Animal* animal);

#endif