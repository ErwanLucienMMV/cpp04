#include "Character.hpp"
#include "AMateria.hpp"

Character::Character() : _name("default")
{
	for (int i = 0; i < 4; ++i)
		_inventory[i] = 0;
}

Character::Character(std::string const &name) : _name(name)
{
	for (int i = 0; i < 4; ++i)
		_inventory[i] = 0;
}

Character::Character(Character const &origin) : _name(origin._name)
{
	for (int i = 0; i < 4; ++i)
		_inventory[i] = 0;
	copyInventory(origin);
}

Character &Character::operator=(Character const &origin)
{
	if (this != &origin)
	{
		clearInventory();
		_name = origin._name;
		copyInventory(origin);
	}
	return (*this);
}

Character::~Character()
{
	clearInventory();
}

void Character::clearInventory()
{
	for (int i = 0; i < 4; ++i)
	{
		delete _inventory[i];
		_inventory[i] = 0;
	}
}

void Character::copyInventory(Character const &origin)
{
	try
	{
		for (int i = 0; i < 4; ++i)
			if (origin._inventory[i])
				_inventory[i] = origin._inventory[i]->clone();
	}
	catch (...)
	{
		clearInventory();
		throw;
	}
}

std::string const &Character::getName() const
{
	return (_name);
}

void Character::equip(AMateria *m)
{
	if (!m)
		return;
	// One pointer must never be owned by two slots of this inventory.
	for (int i = 0; i < 4; ++i)
		if (_inventory[i] == m)
			return;
	for (int i = 0; i < 4; ++i)
	{
		if (!_inventory[i])
		{
			_inventory[i] = m;
			return;
		}
	}
}

void Character::unequip(int idx)
{
	if (idx >= 0 && idx < 4)
		_inventory[idx] = 0;
}

void Character::use(int idx, ICharacter &target)
{
	if (idx >= 0 && idx < 4 && _inventory[idx])
		_inventory[idx]->use(target);
}
