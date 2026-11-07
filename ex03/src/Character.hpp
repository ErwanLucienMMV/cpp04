#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"

class Character : public ICharacter
{
	private:
		std::string _name;
		AMateria *_inventory[4];
		void clearInventory();
		void copyInventory(Character const &origin);

	public:
		Character();
		Character(std::string const &name);
		Character(Character const &origin);
		Character &operator=(Character const &origin);
		virtual ~Character();

		virtual std::string const &getName() const;
		// Ownership transfers only when an empty slot accepts m.
		virtual void equip(AMateria *m);
		// The caller must keep the removed pointer and delete or re-equip it.
		virtual void unequip(int idx);
		virtual void use(int idx, ICharacter &target);
};

#endif
