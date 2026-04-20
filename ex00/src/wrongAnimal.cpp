#include "wrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal") 
{
	std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const std::string& type) : type(type) 
{
	std::cout << "WrongAnimal typed constructor called with type" << type << std::endl;
}

WrongAnimal::~WrongAnimal() 
{
	std::cout << "WrongAnimal destructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &origin) : type(origin.type) 
{
	std::cout << "WrongAnimal copy operator called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal &origin) {
	std::cout << "WrongAnimal copy assignement operator '=' called" << std::endl;
    if (this != &origin) {
        type = origin.type;
    }
    return *this;
}

std::string WrongAnimal::getType() const
{
	return (this->type);
}

void WrongAnimal::makeSound(void) const
{
	std::cout << "Tuezzzz moi (WrongAnimal sound)" << std::endl;
}