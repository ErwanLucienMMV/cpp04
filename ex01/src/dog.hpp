#ifndef DOG_HPP
#define DOG_HPP

#include "brain.hpp"
#include "animal.hpp"

class Dog : public Animal
{
	private:
		Brain *_brain;
	public:
		Dog();
		Dog(const std::string& type); //useless or even dangerous here
		~Dog();
		Dog(const Dog &origin);
		Dog & operator=(const Dog &origin);
		Brain* getBrain();

		void makeSound(void) const /*override*/; //override illegal avec cpp98 mais pas 11
};

#endif