NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

INC = -Isrc/ -Ilibft -Iminilib 

LIB_FLAGS = -Lminilib -lmlx -Llibft -lft -framework OpenGL -framework AppKit

MINILIB = minilib/libmlx.a #minilib/libmlx.dylib

SRC_DIR = ./src/

SRC_FILES = fdf.c parse.c free.c draw.c utils.c event.c
			
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -sC libft
	$(MAKE) -sC minilib 2> /dev/null
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIB_FLAGS) $(MINILIB) -o $(NAME)
	printf "$(ERASE)$(GREEN)Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)created!$(RESET)\n"

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation: $(RESET) $<"

clean:
	$(MAKE) -sC libft clean
	$(MAKE) -sC minilib clean
	printf "$(GREEN)Cleaning up...$(RESET)"
	rm -rf $(OBJS)
	printf "$(ERASE)$(GREEN)Clean finished!$(RESET)"

fclean: clean
	printf "$(ERASE)$(GREEN)Fcleaning up...$(RESET)"
	rm -rf $(NAME)
	rm -rf ./libft/libft.a
	printf "$(ERASE)$(GREEN)Fclean finished!$(RESET)\n"

re: fclean all

.PHONY: $(NAME) all clean fclean re

.SILENT:

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
ERASE = \033[2K\r
RESET = \033[0m
