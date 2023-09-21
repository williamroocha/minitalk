NAME = minitalk
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
SERVER = server
CLIENT = client

SRC_DIR = src
OBJ_DIR = obj

SRC_SERVER = $(addprefix $(SRC_DIR)/server/, server.c)
SRC_CLIENT = $(addprefix $(SRC_DIR)/client/, client.c)

OBJ_SERVER = $(addprefix $(OBJ_DIR)/server/, $(SERVER).o)
OBJ_CLIENT = $(addprefix $(OBJ_DIR)/client/, $(CLIENT).o)

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)/libft.h

IFLAGS = -I./includes -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft

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

$(OBJ_DIR)/server/%.o: $(SRC_DIR)/server/%.c $(LIBFT_INC)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/client/%.o: $(SRC_DIR)/client/%.c $(LIBFT_INC)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) $(SERVER)
	@$(RM) $(CLIENT)
	@echo "cleaned"

re: fclean all

.PHONY: clean fclean all re
