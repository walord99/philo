FILES			= 	main.c \
					print_state.c \
					utils.c \
					atoi.c \
					get_args.c \
					monitor.c \
					inits.c \
					thread.c
							
SRC_DIR			= 	src
OBJ_DIR			= 	obj
SRC				= 	$(addprefix src/, $(FILES))
OBJ 			= 	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
CC				=	gcc

NAME			= 	philo
HEADER_DIR		= 	include

INCLUDES		= 	-I$(HEADER_DIR)
#CC_DEBUG 		= 	-fsanitize=thread #-fno-omit-frame-pointer
#L_DEBUG			=	-fsanitize=thread
ERROR_FLAGS 	= 	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(OBJ) $(L_DEBUG) -o $(NAME)
	@echo "$(CC) $(notdir $(OBJ)) -o $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CC_DEBUG) $(INCLUDES) $(ERROR_FLAGS) -c $< -o $@ -g
	@echo "$(CC) $(CC_DEBUG) $(INCLUDES) $(ERROR_FLAGS) -c $(notdir $<) -o $(notdir $@) -g"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/cstack $(OBJ_DIR)/input_parsing $(OBJ_DIR)/sort  

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

fclean: clean
	make -C $(LIBFT_DIR) fclean

re: clean all                         

.PHONY: all clean fclean re
