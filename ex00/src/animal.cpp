#include "animal.hpp"

Animal::Animal() : type("Animal") 
{
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const std::string& type) : type(type) 
{
	std::cout << "Animal typed constructor called with type" << type << std::endl;
}

Animal::~Animal() 
{
	std::cout << "Animal destructor called" << std::endl;
}

Animal::Animal(const Animal &origin) : type(origin.type) 
{
	std::cout << "Animal copy operator called" << std::endl;
}

Animal& Animal::operator=(const Animal &origin) {
	std::cout << "Animal copy assignement operator '=' called" << std::endl;
    if (this != &origin) {
        type = origin.type;
    }
    return *this;
}

std::string Animal::getType() const
{
	return (this->type);
}

void Animal::makeSound(void) const
{
	std::cout << "Tuezzzz moi (animal sound)" << std::endl;
}