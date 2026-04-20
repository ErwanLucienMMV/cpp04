#include "dog.hpp"

Dog::Dog() : Animal((std::string)"Dog") 
{
	std::cout << "Default Dog constructor called" << std::endl;
}

Dog::~Dog() 
{
	std::cout << "Dog destructor called" << std::endl;
}

Dog::Dog(const Dog &origin) : Animal(origin) 
{
	std::cout << "Copy Dog constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog &origin) {
	std::cout << "Copy and assignement operator constructor called for Dog" << std::endl;
    Animal::operator=(origin);
    return *this;
}

void Dog::makeSound(void) const
{
	std::cout << "*wouf wouf wouf bark* (je veux jouer a la balle)" << std::endl;
}