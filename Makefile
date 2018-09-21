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
		src/scene/scene.o src/scene/handler.o src/scene/scenehandle.o \
		src/intersections/intersections.o src/intersections/sphere.o \
		src/intersections/light.o src/intersections/cone.o \
		src/scene/save.o src/intersections/polygon.o \
		src/intersections/planes.o src/intersections/cylinder.o \
		src/scene/misc.o src/scene/name_handler.o src/scene/search.o \
		src/scene/calc.o src/scene/typehandler.o src/scene/handler2.o \
		src/scene/descene.o src/scene/objects.o src/intersections/shadow.o \
		src/obj_parser/obj_reader.o src/obj_parser/parse_obj.o \
		src/obj_parser/parse_obj_two.o src/obj_parser/parse_obj_three.o \
		src/post_proc/stereo.o src/post_proc/aa.o src/post_proc/oldschool.o \
		src/scene/png.o \


FLAGS = -Wall -Werror -Wextra -I inc -I libft -Ofast -I Renderer -I Vectorlib \
		-I src/scene -I src/intersections -I bmplib/inc/ -I src/obj_parser/ \
		-I upng

LIBS = libft/libft.a Vectorlib/vectorlib.a bmplib/libbmp.a Renderer/renderer.a \
		upng/libpng.a

DEP = inc/rt.h

all:
	make lib
	make $(NAME)

$(NAME): $(LIBS) $(OBJ)
	@echo "[ \x1b[32mLinking $@ \x1b[0m]"
	@gcc $(OBJ) $(FLAGS) $(LIBS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit && echo "\x1b[35m***$(NAME) Ready***\x1b[0m"

$(OBJ): %.o: %.c $(DEP) 
	@echo "[ \x1b[36m \x1b[32mAdding \x1b[33m$@ \x1b[0m]"
	@gcc -c $*.c $(FLAGS) -o $@

lib:
	@make -C libft
	@make -C Vectorlib
	@make -C Renderer
	@make -C bmplib
	@make -C upng

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
	@make clean -C bmplib
	@make clean -C upng
	@rm -f $(OBJ)

fclean: clean
	@echo "[ \x1b[32mFull \x1b[0m]"
	@make -C bmplib fclean
	@make -C Renderer fclean
	@make -C Vectorlib fclean
	@make -C libft fclean
	@make -C upng fclean
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME) g

wolf: all
	./$(NAME) scenes/cylinder.xml

.PHONY: all clean fclean re patience libft run
