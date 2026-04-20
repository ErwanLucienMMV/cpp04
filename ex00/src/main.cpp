#include "animal.hpp"
#include "dog.hpp"
#include "cat.hpp"
#include "wrongCat.hpp"

int main()
{
    std::cout << "===== BASIC CONSTRUCTION TESTS =====" << std::endl;

    Animal a;
    Dog d;
    Cat c;

    std::cout << "\n===== TYPE CHECK TESTS =====" << std::endl;

    std::cout << "Animal type: " << a.getType() << std::endl;
    std::cout << "Dog type: " << d.getType() << std::endl;
    std::cout << "Cat type: " << c.getType() << std::endl;

    std::cout << "\n===== MAKE SOUND TESTS =====" << std::endl;

    a.makeSound();
    d.makeSound();
    c.makeSound();

    std::cout << "\n===== POLYMORPHISM TESTS =====" << std::endl;

    const Animal* metaDog = new Dog();
    const Animal* metaCat = new Cat();

    std::cout << "metaDog type: " << metaDog->getType() << std::endl;
    std::cout << "metaCat type: " << metaCat->getType() << std::endl;

    metaDog->makeSound();
    metaCat->makeSound();

    std::cout << "\n===== COPY TESTS =====" << std::endl;

    Dog dogCopy = d;
    Cat catCopy = c;

    std::cout << "dogCopy type: " << dogCopy.getType() << std::endl;
    std::cout << "catCopy type: " << catCopy.getType() << std::endl;

    dogCopy.makeSound();
    catCopy.makeSound();

    std::cout << "\n===== ASSIGNMENT TESTS =====" << std::endl;

    Dog dogAssign;
    Cat catAssign;

    dogAssign = d;
    catAssign = c;

    std::cout << "dogAssign type: " << dogAssign.getType() << std::endl;
    std::cout << "catAssign type: " << catAssign.getType() << std::endl;

    std::cout << "\n===== CLEANUP TEST =====" << std::endl;

    delete metaDog;
    delete metaCat;

    std::cout << "\n===== END OF PROGRAM =====" << std::endl;

	const WrongAnimal* meta = new WrongAnimal();
	const WrongAnimal* i = new WrongCat();
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the animal sound!
	meta->makeSound();
	
    return 0;
}