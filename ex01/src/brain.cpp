#include "brain.hpp"

Brain::Brain()
{
	std::cout << "Brain constructor called" << std::endl;
}
Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

std::string Brain::getidea(int idea) const
{
	if (idea < 0 || idea >= 100) {
        throw std::out_of_range("Index out of range");
    }
    return this->_ideas[idea];
}

void Brain::setidea(int index, std::string idea)
{
	_ideas[index] = idea;
	std::cout << "idea n: " << index << "set to: " << idea << std::endl;
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