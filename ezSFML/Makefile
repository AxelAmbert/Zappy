##
## EPITECH PROJECT, 2017
## my_printf
## File description:
## Makefiles
##

SRC	=	test_main.cpp \
	    StackElements.cpp   \
	    Graph.cpp \
	    QuickCreate.cpp \
	    GUI.cpp \
	    ButtonClass.cpp \
	    SingleStateButton.cpp \
	    Slider.cpp	\
		Grid.cpp	\
		TextField.cpp	\
		ClassicButton.cpp   \
		CheckBox.cpp    \
		tilesInfosGUI.cpp

OBJ	=	$(SRC:.c=.o)

NAME	=	sfmltest

CFLAGS	=	-Wall -Wextra -I ./ -lncurses -pthread -std=c++17 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME)  $(OBJ) $(CFLAGS)
clean:
	rm -f src/*.o

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:
	rm -rf *.o
