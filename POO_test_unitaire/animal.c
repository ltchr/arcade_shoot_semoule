#include "include/animal.h"
#include <stdio.h>

Animal* animal_constructor(Animal* animal, char* speech){
	animal->speech = speech;
	animal->speak = animal_speak;
	return animal;
}

void animal_speak(Animal* animal){
	printf("%s\n", animal->speech);
}