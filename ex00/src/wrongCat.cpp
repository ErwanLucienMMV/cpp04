#include "wrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal((std::string)"WrongCat") 
{
	std::cout << "Default WrongCat constructor called" << std::endl;
}

WrongCat::~WrongCat() 
{
	std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat &origin) : WrongAnimal(origin) 
{
	std::cout << "Copy WrongCat constructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat &origin) {
	std::cout << "Copy and assignement operator constructor called for WrongCat" << std::endl;
    WrongAnimal::operator=(origin);
    return *this;
}

void WrongCat::makeSound(void) const
{
	std::cout << "*meooooooooooooooooooooooooow* (je veux des croquettes)" << std::endl;
}