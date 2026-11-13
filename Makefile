NAME			= computor
SRCS_DIR		= srcs
OBJ_DIR			= obj
C_FILES			= $(shell find $(SRCS_DIR) -type f -name "*.c")
O_FILES			= $(C_FILES:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
C_FLAGS			= -Wall -Wextra -Werror -Iinclude

all: $(NAME)

$(NAME): $(O_FILES)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(C_FLAGS) -c $^ -o $@

clean:
	rm -rf $(O_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re