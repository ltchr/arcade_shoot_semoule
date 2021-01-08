#include <stdio.h>
#include "include/cow.h"

int main(int argc, char const *argv[])
{
	Cow* cow = new_cow();
	cow->speak((Animal*)cow);

	/* Same as in POO
	* Cow* cow = new Cow();
	* cow->speak();
	*/

	//Animal* animal_cow = (Animal*) cow;
	//animal_cow->speak(animal_cow);	
	return 0;
}