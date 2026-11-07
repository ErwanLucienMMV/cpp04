#ifndef TESTMATERIA_HPP
#define TESTMATERIA_HPP

#include "AMateria.hpp"

// Test fixture: mutable state exposes shallow copies and clone failures.
class TestMateria : public AMateria
{
	private:
		int _uses;
		static int _liveCount;
		static int _cloneCount;
		static int _cloneBudget;

	public:
		TestMateria();
		TestMateria(TestMateria const &origin);
		TestMateria &operator=(TestMateria const &origin);
		virtual ~TestMateria();

		virtual AMateria *clone() const;
		virtual void use(ICharacter &target);
		static int getLiveCount();
		static int getCloneCount();
		static void setCloneBudget(int budget);
};

#endif
