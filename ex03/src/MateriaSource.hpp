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

		// Accepted templates belong to this source; rejected ones to the caller.
		virtual void learnMateria(AMateria *m);
		// Each result is a new clone owned by the caller.
		virtual AMateria *createMateria(std::string const &type);
};

#endif
