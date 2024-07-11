NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

INC = -Isrc/ -Ilibft -Iminilib 

LIB_FLAGS = -Lminilib -lmlx -Llibft -lft -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

MINILIB = minilib/libmlx.a #minilib/libmlx.dylib

SRC_DIR = ./src/

SRC_FILES = fdf.c parse.c free.c draw.c utils.c event.c
			
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -sC libft
	@$(MAKE) -sC minilib 2> /dev/null
	@echo "$(GREEN)Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)creating...$(RESET)"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIB_FLAGS) $(MINILIB) -o $(NAME)
	@echo "$(GREEN)Program$(RESET) $(CYAN)$(BOLD)$(NAME)$(RESET) $(GREEN)created!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(MAKE) -sC libft clean
	@$(MAKE) -sC minilib clean
	@echo "$(GREEN)Cleaning up...$(RESET)"
	@rm -rf $(OBJS)
	@echo "$(GREEN)Clean finished!$(RESET)"

fclean: clean
	@echo "$(GREEN)Fcleaning up...$(RESET)"
	@rm -rf $(NAME)
	@rm -rf ./libft/libft.a
	@echo "$(GREEN)Fclean finished!$(RESET)"

re: fclean all

.PHONY: $(NAME) all clean fclean re

# COLORS
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
BOLD = \033[1m
RESET = \033[0m
