SERVER   = server
CLIENT   = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SOURCES			:=	./sources
INCLUDES		:=	./includes
OBJECTS			:=	./bin
LIBFT			:=	./libft

OBJS			:=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC				:=	gcc
CFLAGS			:=	-Wall -Wextra -Werror
CINCLUDES		:=	-I ${INCLUDES}
CDEPENDENCIES	:=	-L${LIBFT} -lft

BLACK			:=	"\033[1;30m"
RED				:=	"\033[1;31m"
GREEN			:=	"\033[1;32m"
CYAN			:=	"\033[1;35m"
BLUE			:=	"\033[1;36m"
WHITE			:=	"\033[1;37m"
EOC				:=	"\033[0;0m"

${OBJECTS}/%.o: ${SOURCES}/%.c
	@mkdir -p $(dir $@)
	@echo "● Compilation de "$(BLUE)"${notdir $<}"$(EOC)"."
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: ${SERVER} ${CLIENT}
bonus : $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER) : ${OBJECTS}/server.o ${OBJECTS}/error.o ${INCLUDES}/minitalk.h
	@make -C ${LIBFT} --no-print-directory
	@$(CC) ${OBJECTS}/server.o ${OBJECTS}/error.o ${CDEPENDENCIES} -o $@
	@printf "\e[38;5;226m./$@ successfully build\e[0m\n"

$(CLIENT) : ${OBJECTS}/client.o ${OBJECTS}/error.o ${INCLUDES}/minitalk.h
	@$(CC) ${OBJECTS}/client.o ${OBJECTS}/error.o ${CDEPENDENCIES} -o $@
	@printf "\e[38;5;46m./$@ successfully build\e[0m\n"

$(SERVER_BONUS) : ${OBJECTS}/server_bonus.o ${OBJECTS}/error_bonus.o ${INCLUDES}/minitalk_bonus.h
	@make -C ${LIBFT} --no-print-directory
	@$(CC) ${OBJECTS}/server_bonus.o ${OBJECTS}/error_bonus.o ${CDEPENDENCIES} -o server
	@printf "\e[38;5;226m./$@ successfully build\e[0m\n"

$(CLIENT_BONUS) : ${OBJECTS}/client_bonus.o ${OBJECTS}/error_bonus.o ${INCLUDES}/minitalk_bonus.h
	@$(CC) ${OBJECTS}/client_bonus.o ${OBJECTS}/error_bonus.o ${CDEPENDENCIES} -o client
	@printf "\e[38;5;46m./$@ successfully build\e[0m\n"

clean:
	@echo ${GREEN}"● Supression des fichiers binaires (.o)..."$(EOC)
	@make -C ${LIBFT} clean --no-print-directory
	@rm -rf ${OBJECTS}

fclean: clean
	@echo ${GREEN}"● Supression des executables et librairies..."$(EOC)
	@make -C ${LIBFT} fclean --no-print-directory
	@rm -f ${SERVER} ${CLIENT} $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

.PHONY:	all clean fclean re
