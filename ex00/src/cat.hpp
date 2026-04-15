#ifndef CAT_HPP
#define CAT_HPP

#include "animal.hpp"

class Cat : public Animal
{
	public:
		Cat();
		Cat(const std::string& type); //useless or even dangerous here
		~Cat();
		Cat(const Cat &origin);
		Cat & operator=(const Cat &origin);

		void makeSound(void) const /*override*/; //override illegal avec cpp98 mais pas 11
};

#endif