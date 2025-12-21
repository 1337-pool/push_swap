NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0

# Common Source Files (used by both)
COMMON_SRC = srcs/parsing.c srcs/utils.c srcs/split.c \
             srcs/moves_1.c srcs/moves_2.c srcs/sort_utils.c srcs/sort_middle.c
             
BONUS_COMMON_SRC = bonus/parsing_bonus.c bonus/utils_bonus.c bonus/split_bonus.c \
             bonus/moves1_bonus.c bonus/moves2_bonus.c bonus/sort_utils_bonus.c \
             bonus/moves3_bonus.c bonus/utils2_bonus.c

# Mandatory specific
MAIN_SRC = srcs/main.c srcs/sort_big.c 

# Bonus specific
BONUS_SRC = bonus/checker_bonus.c bonus/get_next_line_bonus.c

# Objects
COMMON_OBJ = $(COMMON_SRC:.c=.o)
BONUS_COMMON_OBJ = $(BONUS_COMMON_SRC:.c=.o)
MAIN_OBJ = $(MAIN_SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(COMMON_OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(COMMON_OBJ) $(MAIN_OBJ) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_COMMON_OBJ) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_COMMON_OBJ) $(BONUS_OBJ) -o $(BONUS_NAME)

clean:
	rm -f $(COMMON_OBJ) $(MAIN_OBJ) $(BONUS_OBJ) $(BONUS_COMMON_OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
