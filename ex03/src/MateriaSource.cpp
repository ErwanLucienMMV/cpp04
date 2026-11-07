#include "MateriaSource.hpp"
#include "AMateria.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < 4; ++i)
		_templates[i] = 0;
}

MateriaSource::MateriaSource(MateriaSource const &origin)
{
	for (int i = 0; i < 4; ++i)
		_templates[i] = 0;
	copyTemplates(origin);
}

MateriaSource &MateriaSource::operator=(MateriaSource const &origin)
{
	if (this != &origin)
	{
		clearTemplates();
		copyTemplates(origin);
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
	clearTemplates();
}

void MateriaSource::clearTemplates()
{
	for (int i = 0; i < 4; ++i)
	{
		delete _templates[i];
		_templates[i] = 0;
	}
}

void MateriaSource::copyTemplates(MateriaSource const &origin)
{
	try
	{
		for (int i = 0; i < 4; ++i)
			if (origin._templates[i])
				_templates[i] = origin._templates[i]->clone();
	}
	catch (...)
	{
		clearTemplates();
		throw;
	}
}

void MateriaSource::learnMateria(AMateria *m)
{
	if (!m)
		return;
	for (int i = 0; i < 4; ++i)
		if (_templates[i] == m)
			return;
	for (int i = 0; i < 4; ++i)
	{
		if (!_templates[i])
		{
			_templates[i] = m;
			return;
		}
	}
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < 4; ++i)
		if (_templates[i] && _templates[i]->getType() == type)
			return (_templates[i]->clone());
	return (0);
}
