#include "AMateria.hpp"

AMateria::AMateria() : type("")
{
}

AMateria::AMateria(std::string const &type) : type(type)
{
}

AMateria::AMateria(AMateria const &origin) : type(origin.type)
{
}

AMateria &AMateria::operator=(AMateria const &origin)
{
	// Assignment must preserve the destination Materia's type.
	(void)origin;
	return (*this);
}

AMateria::~AMateria()
{
}

std::string const &AMateria::getType() const
{
	return (type);
}

void AMateria::use(ICharacter &target)
{
	(void)target;
}
