#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria *_templates[4];
		void clearTemplates();
		void copyTemplates(MateriaSource const &origin);

	public:
		MateriaSource();
		MateriaSource(MateriaSource const &origin);
		MateriaSource &operator=(MateriaSource const &origin);
		virtual ~MateriaSource();

		// On success, store a clone and delete the transferred input.
		// Full-source rejection or a throwing clone leaves m with the caller.
		virtual void learnMateria(AMateria *m);
		// Each result is a new clone owned by the caller.
		virtual AMateria *createMateria(std::string const &type);
};

#endif
