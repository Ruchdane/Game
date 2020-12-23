CC = gcc
LL = ld

NAME = mario
BINARIES_DIR = bin
SOURCE_DIR = src
HEADERS_DIR = include /usr/include/SDL2

CFLAGS	=	-g -Werror -Wformat -D_REENTRANT -lSDL2 -lSDL2main \
 			-lSDL2_image -lSDL2_ttf -I include -I /usr/include/SDL2

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
