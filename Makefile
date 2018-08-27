# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibotha <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/06 14:47:39 by ibotha            #+#    #+#              #
#    Updated: 2018/08/25 15:21:05 by ibotha           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

OBJ = src/main.o src/properties.o src/raytracer.o

FLAGS = -Wall -Werror -Wextra -I inc -I libft -Ofast

LIBS = libft/libft.a Vectorlib/vectorlib.a Renderer/renderer.a

DEP = inc/RT.h

all:
	make lib
	make $(NAME)

$(NAME): $(OBJ) $(LIBS)
	@echo "[ \x1b[32mLinking $@ \x1b[0m]"
	@gcc $(OBJ) $(FLAGS) $(LIBS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit && echo "\x1b[35m***$(NAME) Ready***\x1b[0m"

$(OBJ): %.o: %.c $(DEP) 
	@echo "[ \x1b[36m \x1b[32mAdding \x1b[33m$@ \x1b[0m]"
	@gcc -c $*.c $(FLAGS) -o $@

lib:
	@make -C libft
	@make -C Vectorlib
	@make -C Renderer

patience:
	clear
	@echo "\x1b[35mWasting Time: \x1b[32m[#            ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[##           ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[###          ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[####         ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#####        ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[######       ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#######      ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[########     ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#########    ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[##########   ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[###########  ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[############ ]"
	@sleep 1
	clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#############]"
	@sleep 1
	clear;
	@curl parrot.live

clean:
	@echo "[ \x1b[32mCleaning... \x1b[0m]"
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@echo "[ \x1b[32mFull \x1b[0m]"
	@rm -f libft/libft.a
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re patience libft
