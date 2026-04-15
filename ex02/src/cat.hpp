#ifndef CAT_HPP
#define CAT_HPP

#include "brain.hpp"
#include "animal.hpp"

class Cat : public Animal
{
	private:
		Brain *_brain;
	public:
		Cat();
		Cat(const std::string& type); //useless or even dangerous here
		~Cat();
		Cat(const Cat &origin);
		Cat & operator=(const Cat &origin);
		Brain* getBrain();

		void makeSound(void) const /*override*/; //override illegal avec cpp98 mais pas 11
};

#endif