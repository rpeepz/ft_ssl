# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 20:19:37 by rpapagna          #+#    #+#              #
#    Updated: 2019/08/08 21:46:06 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ssl
ARCHIVE = libft/libft.a
AUTHOR	= rpapagna

CFLAGS	= -Wall -Wextra -Werror
INCL	= -I /
OBJ_PATH= obj

#COLOR OUTPUT OPIONS
RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
MAG		=\033[0;35m
NC		=\033[0m

SRCS 	=main.c\
		md5.c

OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))

.PHONY: clean debug

all:	$(NAME)

clean:
		@make -C libft clean
		@rm -rf obj

fclean: clean
		@printf "[$(RED)$(NAME)$(NC)]\tRm binary\n" #PRINT
		@make -C libft fclean
		@rm -rf $(NAME).dSYM
		@rm -rf $(NAME)
		@rm -rf $(NAME).h.gch

re: fclean all

$(NAME):$(OBJ)
		@make -C libft
		@gcc $(CFLAGS) $(OBJ_PATH)/*.o $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG)OK!$(NC)]\n" #PRINT

$(OBJ_PATH):
		@mkdir -p $@

$(OBJ_PATH)/%.o: srcs/%.c | $(OBJ_PATH)
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<

1mo:
		@gcc -g -Wall -Wextra $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG)OK!$(NC)]\n" #PRINT

debug:
		@gcc -g -Wall -Wextra $(addprefix srcs/,$(SRCS)) $(ARCHIVE) -o $(NAME) -fsanitize=address
		@printf "[$(YELLOW)debug$(NC)]\t[$(MAG)OK!$(NC)]\n" #PRINT
