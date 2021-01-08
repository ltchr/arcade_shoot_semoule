#include <stdio.h>
#include "include/cow.h"
#include <stdlib.h>

Cow* new_cow(){
	Cow* cow = calloc(1, sizeof(struct COW_STRUCT));
	Animal* animal = animal_constructor((Animal*)cow, "Mooh Mooh");
	cow->speak = animal->speak;
	return cow;
}