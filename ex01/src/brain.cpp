#include "brain.hpp"

Brain::Brain()
{
	std::cout << "Brain constructor called" << std::endl;
}
Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}
Brain & Brain::operator=(const Brain & brain)
{
	std::cout << "Brain copy assigned operator '=' called" << std::endl;
	if (this != &brain)
	{
		for (int i = 0; i < 100; i++)
			_ideas[i] = brain._ideas[i];
	}
	return (*this);
}