#include "cat.hpp"

Cat::Cat() : Animal((std::string)"Cat") 
{
	std::cout << "Default Cat constructor called" << std::endl;
	this->_brain = new Brain();
}

Cat::Cat(const std::string& type) : Animal(type) 
{
	std::cout << "Named Cat constructor called" << std::endl;
}

Cat::~Cat() 
{
	std::cout << "Cat destructor called" << std::endl;
	if (this->_brain)
		delete this->_brain;
}

Cat::Cat(const Cat &origin) : Animal(origin) 
{
	this->_brain = new Brain(*origin._brain);
	std::cout << "Copy Cat constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat &origin) {
	std::cout << "Copy and assignement operator constructor called for Cat" << std::endl;
    Animal::operator=(origin);
    return *this;
}

void Cat::makeSound(void) const
{
	std::cout << "*meooooooooooooooooooooooooow* (je veux des croquettes)" << std::endl;
}

Brain* Cat::getBrain()
{
	return (this->_brain);
}