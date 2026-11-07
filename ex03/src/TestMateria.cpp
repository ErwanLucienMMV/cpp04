#include "TestMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>
#include <stdexcept>

int TestMateria::_liveCount = 0;
int TestMateria::_cloneCount = 0;
int TestMateria::_cloneBudget = -1;

TestMateria::TestMateria() : AMateria("test"), _uses(0)
{
	++_liveCount;
}

TestMateria::TestMateria(TestMateria const &origin)
	: AMateria(origin), _uses(origin._uses)
{
	++_liveCount;
}

TestMateria &TestMateria::operator=(TestMateria const &origin)
{
	AMateria::operator=(origin);
	_uses = origin._uses;
	return (*this);
}

TestMateria::~TestMateria()
{
	--_liveCount;
}

AMateria *TestMateria::clone() const
{
	if (_cloneBudget == 0)
		throw std::runtime_error("TestMateria clone failed");
	if (_cloneBudget > 0)
		--_cloneBudget;
	AMateria *copy = new TestMateria(*this);
	++_cloneCount;
	return (copy);
}

void TestMateria::use(ICharacter &target)
{
	std::cout << "* test use " << ++_uses << " on " << target.getName()
		<< " *" << std::endl;
}

int TestMateria::getLiveCount()
{
	return (_liveCount);
}

int TestMateria::getCloneCount()
{
	return (_cloneCount);
}

void TestMateria::setCloneBudget(int budget)
{
	_cloneBudget = budget;
}
