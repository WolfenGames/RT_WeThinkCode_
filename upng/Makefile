# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/21 09:04:26 by jwolf             #+#    #+#              #
#    Updated: 2018/09/21 09:15:24 by jwolf            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libpng.a

CFLAGS += -Wextra -Wall -I./

ATTACH = 

C = gcc

SOURCES = upng.c png2tga.c

OBJECTS = $(SOURCES:.c=.o)

%.o:		%.c upng.h
	@echo "\033[1;35;m[Compiling $<] \t\033[0m"
	@$(C) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@echo "\033[1;34;m[Making... Pizza]\033[0m"
	@ar rcs $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "\033[1;34;m[Pnglib made]\033[0m"

all: $(NAME)

clean:
	@echo "\033[1;33;m[Cleaning]\033[0m"
	@rm -rf $(OBJECTS)

fclean: clean
	@echo "\033[1;32;m[Force Cleaning]\033[0m"
	@rm -rf $(NAME)

re: fclean clean all
	@echo "\033[1;31;m[Recompiled]\033[0m"

.PHONY: fclean clean all re