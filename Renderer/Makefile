# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/12 13:11:21 by ibotha            #+#    #+#              #
#    Updated: 2018/09/05 16:36:31 by ibotha           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = renderer.a
HED = renderer.h
OBJ = draw.o setup.o hooks.o colour.o window_manage.o select.o image.o del.o

all: $(NAME)

$(NAME): $(OBJ)
	@echo "[ \x1b[35mLinking... \x1b[0m]"
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "[ \x1b[34mLinked $(NAME) \x1b[0m]\n"

$(OBJ): %.o: %.c $(HED)
	@echo "[ \x1b[32mAdding \x1b[33m$@ \x1b[0m]"
	@gcc -c $*.c -o $@ -Wall -Werror -Wextra -I ../libft

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f $(OBJ)

re: fclean all

.PHONY: all fclean clean re
