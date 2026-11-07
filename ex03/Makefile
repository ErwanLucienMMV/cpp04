RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

SRC = src/main.cpp \
	src/AMateria.cpp \
	src/ICharacter.cpp \
	src/IMateriaSource.cpp \
	src/Ice.cpp \
	src/Cure.cpp \
	src/Character.cpp \
	src/MateriaSource.cpp

NAME = interfaceRecap

OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

FLAGS = -std=c++98 -Wall -Werror -Wextra

CXX = c++

all	: $(NAME)

$(NAME)	: $(OBJ)
	@printf '%b\n' "$(YELLOW)[$(NAME)] $(GREEN).o created $(RESET)"
	@$(CXX) $(FLAGS) $(OBJ) -o $(NAME)
	@printf '%b\n' "$(YELLOW)[$(NAME)] $(GREEN)executable created successfully$(RESET)"

%.o: %.cpp
	@$(CXX) $(FLAGS) -MMD -MP -c $< -o $@

clean	:
	@rm -f $(OBJ) $(DEP)
	@printf '%b\n' "$(YELLOW)[$(NAME)] $(RED).o deleted$(RESET)"

fclean	: clean
	@rm -f $(NAME)
	@printf '%b\n' "$(YELLOW)[$(NAME)] $(RED)executable deleted$(RESET)"
	@printf '%b\n' "$(YELLOW)[$(NAME)] $(GREEN)forced clean successful$(RESET)"

re	: fclean
	@$(MAKE) --no-print-directory all

-include $(DEP)

.PHONY: all clean fclean re
