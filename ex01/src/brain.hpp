#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <iostream>

class Brain
{
	private:
		std::string _ideas[100];
	public:
		Brain();
		~Brain();
		Brain & operator=(const Brain & brain);
		std::string getidea(int idea) const;
		void setidea(int index, std::string idea);
	
};

#endif
