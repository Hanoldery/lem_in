# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Pierre <Pierre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 14:30:42 by pgerbaud          #+#    #+#              #
#    Updated: 2018/02/03 19:21:40 by pgerbaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem-in

SRC = 	main \
		algo \
		struct_utils \
		parser \
		parser_utils \
		output
OBJ=$(foreach lem, $(SRC), src/$(lem).o)

LIB = src/libft
INC = ./includes ./$(LIB)/includes

CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += $(foreach path, $(INC), -I$(path))

# ----------- COLORS -----------
LOG_U		:= \033[A
STOP_C		:= \x1b[0m
OK_C		:= \033[0;32m
ERROR_C		:= \x1b[31;01m
WARN_C		:= \x1b[33;01m
SILENT_C	:= \x1b[29;01m
CHARS		:= / / - - \\ \\ | |
INCR		:= 1
# -------------------------------

all : $(NAME)
	@printf "\n"

src/%.o : src/%.c
	@printf "$(LOG_U)$(WARN_C)[%s]$(STOP_C) Compiling : %s          \
		\n" "$(word $(INCR), $(CHARS))" "$@"
	@$(eval INCR = $(shell echo $$(($(INCR) % 8 + 1))))
	@gcc -o $@ -c $< $(CFLAGS) $(CFLAGS)

$(NAME) : $(OBJ)
	@make -C $(LIB)
	@gcc $(CLFAGS) $^ -L$(LIB) -lft -o $@
	@printf "$(LOG_U)$(OK_C)[OK]$(STOP_C) Compiling done for\
	 $(SILENT_C)%s$(STOP_C)       \n" "$@"
	@printf "\n"

clean :
	@make -C $(LIB) clean
	@rm -f $(OBJ)

fclean : clean
	@make -C $(LIB) fclean
	@printf "$(LOG_U)$(ERROR_C)[RM]$(STOP_C) $(SILENT_C)%s$(STOP_C) Deleted\n" "$(NAME)"
	@printf "\n"
	@rm -f $(NAME)

re : fclean all

fclean-nolib :
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@printf "\n"
	@printf "$(LOG_U)$(ERROR_C)[RM]$(STOP_C) $(SILENT_C)%s$(STOP_C) Deleted\n" "$(NAME)"
	@printf "\n"

re-nolib : fclean-nolib $(NAME)

.PHONY : all clean fclean re re-nolib fclean-nolib
