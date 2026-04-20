#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal
{
	protected:
		std::string type;
	
	public:
		WrongAnimal();
		WrongAnimal(const std::string& type);
		virtual ~WrongAnimal();
		WrongAnimal(const WrongAnimal &origin);
		WrongAnimal & operator=(const WrongAnimal &origin);

		std::string getType() const;

		void makeSound(void) const;
};

#endif