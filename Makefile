# Name of the project
NAME = minitalk

# Compiler and flags
CC = cc
FLAGS = -Wall -Wextra -Werror

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
LIBFT_INC = $(LIBFT_DIR)/libft.h

# Include and library flags
IFLAGS = -I./includes -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft

# Default rule: Compiles the project
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(SERVER) $(CLIENT)
	@echo "Done"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(SERVER): $(OBJ_SERVER)
	@$(CC) $(FLAGS) $(OBJ_SERVER) -o $(SERVER) $(LFLAGS)
	@echo "server created"

$(CLIENT): $(OBJ_CLIENT)
	@$(CC) $(FLAGS) $(OBJ_CLIENT) -o $(CLIENT) $(LFLAGS)
	@echo "client created"

# Compiles server and client object files
$(OBJ_DIR)/server/%.o: $(SRC_DIR)/server/%.c $(LIBFT_INC)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/client/%.o: $(SRC_DIR)/client/%.c $(LIBFT_INC)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

# Bonus rules: Compiles the bonus part of the project
bonus: $(LIBFT) $(OBJ_DIR) $(BONUS_SERVER) $(BONUS_CLIENT)
	@echo "Bonus Done"

$(BONUS_SERVER): $(BONUS_OBJ_SERVER)
	@$(CC) $(FLAGS) $(BONUS_OBJ_SERVER) -o $(BONUS_SERVER) $(LFLAGS)
	@echo "server_bonus created"

$(BONUS_CLIENT): $(BONUS_OBJ_CLIENT)
	@$(CC) $(FLAGS) $(BONUS_OBJ_CLIENT) -o $(BONUS_CLIENT) $(LFLAGS)
	@echo "client_bonus created"

# Cleaning rules
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Objects cleaned"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) $(SERVER) $(CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT)
	@echo "All cleaned"

# Re-compilation rules
re: fclean all
bonus_re: fclean bonus

.PHONY: clean fclean all re bonus bonus_re
