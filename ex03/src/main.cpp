#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include "TestMateria.hpp"
#include <climits>
#include <iostream>
#include <sstream>
#include <stdexcept>

static void check(bool condition, std::string const &message)
{
	if (!condition)
		throw std::runtime_error(message);
}

static void checkUse(ICharacter &user, int idx, ICharacter &target,
	std::string const &expected)
{
	std::ostringstream output;
	std::streambuf *saved = std::cout.rdbuf(output.rdbuf());
	try
	{
		user.use(idx, target);
	}
	catch (...)
	{
		std::cout.rdbuf(saved);
		throw;
	}
	std::cout.rdbuf(saved);
	check(output.str() == expected, "Unexpected output from Character::use");
}

static void subjectExample()
{
	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter *me = new Character("me");
	AMateria *tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter *bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete bob;
	delete me;
	delete src;
}

static void testMateria()
{
	Ice ice;
	Ice iceCopy(ice);
	Ice iceAssigned;
	iceAssigned = iceCopy;
	Cure cure;
	Cure cureCopy(cure);
	Cure cureAssigned;
	cureAssigned = cureCopy;
	AMateria &base = ice;
	base = cure;
	check(ice.getType() == "ice", "Base assignment changed the Materia type");
	check(iceAssigned.getType() == "ice", "Ice copy has the wrong type");
	check(cureAssigned.getType() == "cure", "Cure copy has the wrong type");
	AMateria *iceClone = ice.clone();
	AMateria *cureClone = cure.clone();
	check(iceClone != &ice && iceClone->getType() == "ice", "Invalid Ice clone");
	check(cureClone != &cure && cureClone->getType() == "cure", "Invalid Cure clone");
	delete iceClone;
	delete cureClone;
	std::cout << "[OK] Materia types, canonical copies and clones" << std::endl;
}

static void testInventory()
{
	Character me("me");
	Character target("bob");
	for (int i = 0; i < 4; ++i)
		checkUse(me, i, target, "");
	me.equip(0);
	me.unequip(-1);
	me.unequip(4);
	me.unequip(INT_MIN);
	me.unequip(INT_MAX);
	checkUse(me, -1, target, "");
	checkUse(me, 4, target, "");
	checkUse(me, INT_MIN, target, "");
	checkUse(me, INT_MAX, target, "");

	AMateria *floor = new Ice();
	me.equip(floor);
	me.equip(floor);
	// A duplicate pointer must not occupy a second slot.
	checkUse(me, 1, target, "");
	me.equip(new Cure());
	me.equip(new Ice());
	me.equip(new Cure());
	AMateria *rejected = new Ice();
	me.equip(rejected);
	delete rejected;
	checkUse(me, 0, target, "* shoots an ice bolt at bob *\n");
	checkUse(me, 1, target, "* heals bob's wounds *\n");
	checkUse(me, 2, target, "* shoots an ice bolt at bob *\n");
	checkUse(me, 3, target, "* heals bob's wounds *\n");

	// Save the address before unequipping: Character must not delete it.
	me.unequip(0);
	me.unequip(0);
	checkUse(me, 0, target, "");
	check(floor->getType() == "ice", "unequip deleted the Materia");
	me.equip(new Cure());
	checkUse(me, 0, target, "* heals bob's wounds *\n");
	Character other("other");
	other.equip(floor);
	checkUse(other, 0, target, "* shoots an ice bolt at bob *\n");
	other.unequip(0);
	delete floor;
	std::cout << "[OK] Four slots, first free slot, invalid indices and unequip"
		<< std::endl;
}

static void testCharacterCopies()
{
	Character target("bob");
	Character assigned;
	assigned.equip(new Cure());
	Character *copy;
	{
		Character original("original");
		AMateria *floor = new Cure();
		original.equip(new Ice());
		original.equip(floor);
		original.equip(new Cure());
		original.equip(new Ice());
		original.unequip(1);
		delete floor;
		copy = new Character(original);
		assigned = original;
		Character &alias = original;
		original = alias;
		checkUse(original, 0, target, "* shoots an ice bolt at bob *\n");
	}
	// The original is destroyed; both copies must still own valid clones.
	check(copy->getName() == "original", "Copy constructor lost the name");
	check(assigned.getName() == "original", "Assignment lost the name");
	checkUse(*copy, 0, target, "* shoots an ice bolt at bob *\n");
	checkUse(*copy, 1, target, "");
	checkUse(*copy, 2, target, "* heals bob's wounds *\n");
	checkUse(*copy, 3, target, "* shoots an ice bolt at bob *\n");
	delete copy;
	checkUse(assigned, 0, target, "* shoots an ice bolt at bob *\n");
	checkUse(assigned, 1, target, "");
	checkUse(assigned, 2, target, "* heals bob's wounds *\n");
	checkUse(assigned, 3, target, "* shoots an ice bolt at bob *\n");
	Character empty("empty");
	assigned = empty;
	Character emptyCopy(empty);
	for (int i = 0; i < 4; ++i)
	{
		checkUse(assigned, i, target, "");
		checkUse(emptyCopy, i, target, "");
	}
	std::cout << "[OK] Character deep copies, holes, self-assignment and replacement"
		<< std::endl;
}

static void checkCreated(MateriaSource &source, std::string const &type)
{
	AMateria *first = source.createMateria(type);
	AMateria *second = source.createMateria(type);
	check(first && second && first != second, "Source did not return fresh clones");
	check(first->getType() == type && second->getType() == type,
		"Source returned the wrong type");
	delete first;
	delete second;
}

static void testSource()
{
	MateriaSource source;
	check(source.createMateria("ice") == 0, "Empty source created a Materia");
	source.learnMateria(0);
	AMateria *ice = new Ice();
	source.learnMateria(ice);
	source.learnMateria(new Ice());
	source.learnMateria(new Ice());
	source.learnMateria(new Cure());
	checkCreated(source, "ice");
	checkCreated(source, "cure");
	AMateria *rejected = new Cure();
	source.learnMateria(rejected);
	delete rejected;
	check(source.createMateria("fire") == 0, "Unknown type was accepted");
	check(source.createMateria("Ice") == 0, "Types must be case sensitive");
	check(source.createMateria("") == 0, "Unknown empty type was accepted");
	// A created Materia must also outlive its source.
	AMateria *independent;
	{
		MateriaSource temporary;
		temporary.learnMateria(new Ice());
		independent = temporary.createMateria("ice");
	}
	check(independent->getType() == "ice", "Created Materia depends on its source");
	delete independent;
	std::cout << "[OK] Source limits, duplicate types, unknown types and fresh clones"
		<< std::endl;
}

static void testSourceCopies()
{
	MateriaSource assigned;
	assigned.learnMateria(new Ice());
	MateriaSource *copy;
	{
		MateriaSource original;
		original.learnMateria(new Cure());
		original.learnMateria(new Ice());
		copy = new MateriaSource(original);
		assigned = original;
		MateriaSource &alias = original;
		original = alias;
		checkCreated(original, "cure");
	}
	checkCreated(*copy, "ice");
	checkCreated(*copy, "cure");
	delete copy;
	checkCreated(assigned, "ice");
	checkCreated(assigned, "cure");
	MateriaSource empty;
	MateriaSource emptyCopy(empty);
	assigned = empty;
	check(assigned.createMateria("ice") == 0, "Assignment retained an old template");
	check(emptyCopy.createMateria("cure") == 0, "Copy of empty source is not empty");
	std::cout << "[OK] Source deep copies, self-assignment and replacement" << std::endl;
}

static void testCustomMateria()
{
	check(TestMateria::getLiveCount() == 0, "Unexpected live test Materia");
	{
		MateriaSource source;
		int clones = TestMateria::getCloneCount();
		source.learnMateria(new TestMateria());
		check(TestMateria::getCloneCount() == clones + 1,
			"learnMateria must copy the input through clone");
		check(TestMateria::getLiveCount() == 1,
			"Successful learning must release the transferred input");
		for (int i = 1; i < 4; ++i)
			source.learnMateria(new TestMateria());
		check(TestMateria::getCloneCount() == clones + 4
			&& TestMateria::getLiveCount() == 4,
			"Duplicate types must occupy separate template slots");
		AMateria *rejected = new Cure();
		source.learnMateria(rejected);
		check(source.createMateria("cure") == 0,
			"Full source accepted a fifth template");
		delete rejected;
		Character target("bob");
		Character original("original");
		original.equip(source.createMateria("test"));
		checkUse(original, 0, target, "* test use 1 on bob *\n");
		Character copy(original);
		Character assigned;
		assigned.equip(new TestMateria());
		assigned = original;
		checkUse(original, 0, target, "* test use 2 on bob *\n");
		checkUse(original, 0, target, "* test use 3 on bob *\n");
		checkUse(copy, 0, target, "* test use 2 on bob *\n");
		checkUse(assigned, 0, target, "* test use 2 on bob *\n");
		Character fresh("fresh");
		fresh.equip(source.createMateria("test"));
		checkUse(fresh, 0, target, "* test use 1 on bob *\n");
		MateriaSource sourceCopy(source);
		Character fromCopy("from copy");
		fromCopy.equip(sourceCopy.createMateria("test"));
		checkUse(fromCopy, 0, target, "* test use 1 on bob *\n");
	}
	check(TestMateria::getLiveCount() == 0, "Custom Materia leaked");
	std::cout << "[OK] Learning copies, custom Materia and independent mutable state"
		<< std::endl;
}

static void testCloneFailures()
{
	{
		MateriaSource source;
		AMateria *input = new TestMateria();
		TestMateria::setCloneBudget(0);
		bool failed = false;
		try
		{
			source.learnMateria(input);
		}
		catch (std::runtime_error const &)
		{
			failed = true;
		}
		check(failed && TestMateria::getLiveCount() == 1,
			"Failed learning must retain caller ownership of the input");
		check(source.createMateria("test") == 0,
			"Failed learning changed the source");
		delete input;
		TestMateria::setCloneBudget(-1);
		source.learnMateria(new TestMateria());
		source.learnMateria(new TestMateria());
		TestMateria::setCloneBudget(1);
		failed = false;
		try
		{
			MateriaSource copy(source);
		}
		catch (std::runtime_error const &)
		{
			failed = true;
		}
		check(failed && TestMateria::getLiveCount() == 2,
			"Failed source copy leaked a partial clone");
		TestMateria::setCloneBudget(-1);
		Character original("original");
		original.equip(source.createMateria("test"));
		original.equip(source.createMateria("test"));
		TestMateria::setCloneBudget(1);
		failed = false;
		try
		{
			Character copy(original);
		}
		catch (std::runtime_error const &)
		{
			failed = true;
		}
		check(failed && TestMateria::getLiveCount() == 4,
			"Failed Character copy leaked a partial clone");
		TestMateria::setCloneBudget(-1);
	}
	check(TestMateria::getLiveCount() == 0, "Clone failure leaked a Materia");
	std::cout << "[OK] Throwing clones preserve ownership and clean partial copies"
		<< std::endl;
}

int main()
{
	try
	{
		subjectExample();
		testMateria();
		testInventory();
		testCharacterCopies();
		testSource();
		testSourceCopies();
		testCustomMateria();
		testCloneFailures();
	}
	catch (std::exception const &error)
	{
		std::cout << "[FAIL] " << error.what() << std::endl;
		return (1);
	}
	std::cout << "All tests passed." << std::endl;
	return (0);
}
