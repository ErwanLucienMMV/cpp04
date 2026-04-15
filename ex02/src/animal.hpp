#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal
{
	protected:
		std::string type;
	
	public:
		Animal();
		Animal(const std::string& type);
		virtual ~Animal();
		Animal(const Animal &origin);
		Animal & operator=(const Animal &origin);

		std::string getType() const;

		virtual void makeSound(void) const = 0;
};

#endif