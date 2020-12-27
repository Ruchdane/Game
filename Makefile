CC = gcc
LL = ld

NAME = mario
BINARIES_DIR = bin
SOURCE_DIR = src
HEADERS_DIR = include /usr/include/SDL2

CFLAGS	=	-g -Werror -Wformat `pkg-config --cflags --libs sdl2 SDL2_image SDL2_ttf` -I include

SRC = $(shell ls src/)
OBJ = $(SRC:.c=.o)

vpath %.c $(SOURCE_DIR)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(BINARIES_DIR)/$(NAME) $(CFLAGS)

clean:
	rm -f -r $(OBJ)

obj : 
	$(OBJ)

mproper:  clean
	rm -f -r $(BINARIES_DIR)/$(NAME)
