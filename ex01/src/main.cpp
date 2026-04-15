#include "animal.hpp"
#include "dog.hpp"
#include "cat.hpp"

int main()
{
	{
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		delete j;//should not create a leak
		delete i;
	}
	std::cout << "===== BASIC POLYMORPHIC DELETE TEST =====" << std::endl;

    const Animal* j = new Dog();
    const Animal* i = new Cat();

    delete j; // must call Dog + Brain + Animal destructors
    delete i;
	{
    std::cout << "\n===== ARRAY CREATION =====" << std::endl;

    const int size = 10;
    Animal* animals[size];

    // Fill half Dog, half Cat
    for (int i = 0; i < size / 2; i++)
        animals[i] = new Dog();

    for (int i = size / 2; i < size; i++)
        animals[i] = new Cat();

    std::cout << "\n===== TESTING SOUNDS =====" << std::endl;

    for (int i = 0; i < size; i++)
        animals[i]->makeSound();

    std::cout << "\n===== COPY TEST (NO BRAIN ACCESS) =====" << std::endl;

    Dog originalDog;
    Dog copyDog(originalDog);

    Cat originalCat;
    Cat copyCat(originalCat);

    std::cout << "Copy constructors executed successfully" << std::endl;

    std::cout << "\n===== ASSIGNMENT TEST =====" << std::endl;

    Dog assignDog;
    assignDog = originalDog;

    Cat assignCat;
    assignCat = originalCat;

    std::cout << "Assignment operators executed successfully" << std::endl;

    std::cout << "\n===== CLEANUP =====" << std::endl;

    for (int i = 0; i < size; i++)
        delete animals[i];

    std::cout << "\n===== END =====" << std::endl;
	}
	return 0;
}