# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwolf <jwolf@42.FR>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/06 14:47:39 by ibotha            #+#    #+#              #

#    Updated: 2018/09/03 15:05:14 by jwolf            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

OBJ = src/main.o src/properties.o src/raytracer.o src/loading.o src/blocks.o \
		src/scene/scene.o src/scene/handler.o src/scene/scenehandle.c \
		src/intersections/intersections.o src/intersections/sphere.o \
		src/intersections/light.o \
		src/scene/misc.o src/scene/name_handler.o src/scene/search.o \
		src/scene/calc.o src/scene/typehandler.o src/scene/handler2.o \
		src/scene/descene.o src/scene/objects.o


FLAGS = -Wall -Werror -Wextra -I inc -I libft -Ofast -I Renderer -I Vectorlib \
		-I src/scene -I src/intersections

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
	@clear
	@echo "\x1b[35mWasting Time: \x1b[32m[#            ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[##           ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[###          ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[####         ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#####        ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[######       ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#######      ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[########     ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#########    ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[##########   ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[###########  ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[############ ]"
	@sleep 1
	@clear;
	@echo "\x1b[35mWasting Time: \x1b[32m[#############]"
	@sleep 1
	@clear;
	@curl parrot.live

clean:
	@echo "[ \x1b[32mCleaning... \x1b[0m]"
	@make clean -C libft
	@make clean -C Renderer
	@make clean -C Vectorlib
	@rm -f $(OBJ)

fclean: clean
	@echo "[ \x1b[32mFull \x1b[0m]"
	@rm -f libft/libft.a
	@rm -f Renderer/renderer.a
	@rm -f Vectorlib/vectorlib.a
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) g

wolf: all
	@make clean
	./$(NAME) scenes/Example.xml

.PHONY: all clean fclean re patience libft run
