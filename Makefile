# Name of the project
NAME = minitalk

# Compiler and flags
CC = gcc
FLAGS = -Wall -Wextra -Werror -fPIE

# Target names
SERVER = server
CLIENT = client
BONUS_SERVER = server_bonus
BONUS_CLIENT = client_bonus

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj

# Source files for main and bonus parts
SRC_SERVER = $(addprefix $(SRC_DIR)/server/, server.c)
SRC_CLIENT = $(addprefix $(SRC_DIR)/client/, client.c)
BONUS_SRC_SERVER = $(addprefix $(SRC_DIR)/server/, server_bonus.c)
BONUS_SRC_CLIENT = $(addprefix $(SRC_DIR)/client/, client_bonus.c)

# Object files for main and bonus parts
OBJ_SERVER = $(addprefix $(OBJ_DIR)/server/, $(SERVER).o)
OBJ_CLIENT = $(addprefix $(OBJ_DIR)/client/, $(CLIENT).o)
BONUS_OBJ_SERVER = $(addprefix $(OBJ_DIR)/server/, $(BONUS_SERVER).o)
BONUS_OBJ_CLIENT = $(addprefix $(OBJ_DIR)/client/, $(BONUS_CLIENT).o)

# Libft directory and its targets
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Include and library flags
IFLAGS = -I./includes -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft

# Default rule: Compiles the project
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(SERVER) $(CLIENT)
	@echo "Compilation Done"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(SERVER): $(OBJ_SERVER)
	@if [ ! -e $(SERVER) ] || [ $(OBJ_SERVER) -nt $(SERVER) ]; then \
		$(CC) $(FLAGS) -pie $(OBJ_SERVER) -o $(SERVER) $(LFLAGS); \
		echo "server created"; \
	else \
		echo "server is up-to-date"; \
	fi

$(CLIENT): $(OBJ_CLIENT)
	@if [ ! -e $(CLIENT) ] || [ $(OBJ_CLIENT) -nt $(CLIENT) ]; then \
		$(CC) $(FLAGS) $(OBJ_CLIENT) -o $(CLIENT) $(LFLAGS); \
		echo "client created"; \
	else \
		echo "client is up-to-date"; \
	fi

# Compiles server and client object files
$(OBJ_DIR)/server/%.o: $(SRC_DIR)/server/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/client/%.o: $(SRC_DIR)/client/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

# Bonus rules: Compiles the bonus part of the project
bonus: $(LIBFT) $(OBJ_DIR) $(BONUS_SERVER) $(BONUS_CLIENT)
	@echo "Bonus Compilation Done"

$(BONUS_SERVER): $(BONUS_OBJ_SERVER)
	@if [ ! -e $(BONUS_SERVER) ] || [ $(BONUS_OBJ_SERVER) -nt $(BONUS_SERVER) ]; then \
		$(CC) $(FLAGS) $(BONUS_OBJ_SERVER) -o $(BONUS_SERVER) $(LFLAGS); \
		echo "server_bonus created"; \
	else \
		echo "server_bonus is up-to-date"; \
	fi

$(BONUS_CLIENT): $(BONUS_OBJ_CLIENT)
	@if [ ! -e $(BONUS_CLIENT) ] || [ $(BONUS_OBJ_CLIENT) -nt $(BONUS_CLIENT) ]; then \
		$(CC) $(FLAGS) $(BONUS_OBJ_CLIENT) -o $(BONUS_CLIENT) $(LFLAGS); \
		echo "client_bonus created"; \
	else \
		echo "client_bonus is up-to-date"; \
	fi

# Cleaning rules
clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Objects cleaned"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -f $(SERVER) $(CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT)
	@echo "All cleaned"

# Re-compilation rules
re: fclean all
bonus_re: fclean bonus

.PHONY: clean fclean all re bonus bonus_re
