# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Pierre <Pierre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 14:30:42 by pgerbaud          #+#    #+#              #
#    Updated: 2018/01/31 17:05:51 by pgerbaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

CFLAGS=-Wall -Wextra -Werror

SRC = 	ft_atoi \
		ft_atoimax \
		ft_bzero \
		ft_imaxtoa \
		ft_imaxtoa_base \
		ft_inttabclr \
		ft_inttabdisplay \
		ft_inttabfind \
		ft_iprintsize \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isnumber \
		ft_isprint \
		ft_itoa \
		ft_lstadd \
		ft_lstdel \
		ft_lstdelone \
		ft_lstiter \
		ft_lstmap \
		ft_lstnew \
		ft_memalloc \
		ft_memccpy \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memdel \
		ft_memmove \
		ft_memset \
		ft_putchar \
		ft_putchar_fd \
		ft_putendl \
		ft_putendl_fd \
		ft_putnbr \
		ft_putnbr_fd \
		ft_putstr \
		ft_putstr_fd \
		ft_putstr_fdret \
		ft_straddinstr \
		ft_strcat \
		ft_strchr \
		ft_strclr \
		ft_strcmp \
		ft_strcpy \
		ft_strcut \
		ft_strdel \
		ft_strdelinside \
		ft_strdelret \
		ft_strdup \
		ft_strequ \
		ft_strfill \
		ft_strfind \
		ft_strisnumber \
		ft_striter \
		ft_striteri \
		ft_strjoin \
		ft_strjoinfree \
		ft_strjoinfreefirst \
		ft_strlcat \
		ft_strlen \
		ft_strmap \
		ft_strmapi \
		ft_strmchr \
		ft_strmintchr \
		ft_strncat \
		ft_strncmp \
		ft_strncpy \
		ft_strnequ \
		ft_strnew \
		ft_strnstr \
		ft_strrchr \
		ft_strsplit \
		ft_strstr \
		ft_strsub \
		ft_strtrim \
		ft_tolower \
		ft_toupper \
		ft_uimaxtoa \
		ft_uimaxtoa_base \
		ft_uiprintsize

INC=./includes

OBJ=$(foreach libft, $(SRC), $(libft).o)

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

%.o : %.c
	@printf "$(LOG_U)$(WARN_C)[%s]$(STOP_C) Compiling : %s          \
		\n" "$(word $(INCR), $(CHARS))" "$@"
	@$(eval INCR = $(shell echo $$(($(INCR) % 8 + 1))))
	@gcc -o $@ -c $< $(CFLAGS) -I$(INC)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "$(LOG_U)$(OK_C)[OK]$(STOP_C) Compiling done for\
	 $(SILENT_C)%s$(STOP_C)       \n" "$@"

clean :
	@rm -f $(OBJ)

fclean : clean
	@printf "$(ERROR_C)[RM]$(STOP_C) $(SILENT_C)%s$(STOP_C) Deleted\n" "$(NAME)"
	@printf "\n"
	@rm -f $(NAME)

re : fclean all
