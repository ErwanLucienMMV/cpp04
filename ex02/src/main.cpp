#include "animal.hpp"
#include "dog.hpp"
#include "cat.hpp"
#include <iostream>

int main()
{
    std::cout << "===== ABSTRACT TEST =====" << std::endl;

    // Animal a = new Animal(); // MUST NOT COMPILE (keep commented)

    std::cout << "\n===== POLYMORPHISM TEST =====" << std::endl;

    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    dog->makeSound();
    cat->makeSound();

    std::cout << "\n===== DELETE TEST =====" << std::endl;

    delete dog;
    delete cat;

    std::cout << "\n===== ARRAY TEST =====" << std::endl;

    const int size = 10;
    Animal* animals[size];

    for (int i = 0; i < size / 2; i++)
        animals[i] = new Dog();

    for (int i = size / 2; i < size; i++)
        animals[i] = new Cat();

    for (int i = 0; i < size; i++)
        animals[i]->makeSound();

    std::cout << "\n===== CLEANUP =====" << std::endl;

    for (int i = 0; i < size; i++)
        delete animals[i];

    std::cout << "\n===== COPY TEST =====" << std::endl;

    Dog a;
    Dog b = a;      // copy constructor
    Dog c;

    c = a;          // assignment operator

    std::cout << "Copy & assignment executed" << std::endl;

    std::cout << "\n===== END =====" << std::endl;

    return 0;
}