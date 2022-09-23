SERVER   = server
CLIENT   = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
CC	     = gcc
FLAGS    = -Wall -Werror -Wextra
LIBS	 = -L./libft -lft
LIBFT	 = libft.a

all : $(LIBFT) $(SERVER) $(CLIENT)
bonus : $(LIBFT) $(SERVER_BONUS) $(CLIENT_BONUS)

$(LIBFT) :
	@make -C libft

$(SERVER) : server.o minitalk.h
	@$(CC) server.o $(LIBS) -o $@
	@printf "\e[38;5;226m./$@ successfully build\e[0m\n"

$(CLIENT) : client.o error.o minitalk.h
	@$(CC) client.o error.o $(LIBS) -o $@
	@printf "\e[38;5;46m./$@ successfully build\e[0m\n"

$(SERVER_BONUS): server_bonus.o minitalk.h
	@$(CC) server_bonus.o $(LIBS) -o server
	@printf "\e[38;5;226m./$@ successfully build\e[0m\n"

$(CLIENT_BONUS) : client_bonus.o error.o minitalk.h
	@$(CC) client_bonus.o error.o $(LIBS) -o client
	@printf "\e[38;5;46m./$@ successfully build\e[0m\n"

%.o : %.c
	@$(CC) $(FLAGS) $< -c -I includes

clean :
	@make clean -C libft
	@rm -f *.o
	@printf "\e[38;5;206m.o files deleted🚽\e[0m\n"

fclean: clean
	@make fclean -C libft
	@rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	@printf "\e[38;5;200mBinaries deleted🗑\e[0m\n"

re: fclean all
