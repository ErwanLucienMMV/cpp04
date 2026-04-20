#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "wrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
	public:
		WrongCat();
		WrongCat(const std::string& type); //useless or even dangerous here
		~WrongCat();
		WrongCat(const WrongCat &origin);
		WrongCat & operator=(const WrongCat &origin);

		void makeSound(void) const /*override*/; //override illegal avec cpp98 mais pas 11
};

#endif