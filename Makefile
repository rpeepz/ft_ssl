# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 20:19:37 by rpapagna          #+#    #+#              #
#    Updated: 2019/11/01 23:36:05 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ssl
ARCHIVE = libft/libft.a
AUTHOR	= rpapagna

CFLAGS	= -Wall -Wextra
INCL	= -I ./
OBJ_PATH= obj

#COLOR OUTPUT OPIONS
RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
MAG		=\033[0;35m
NC		=\033[0m

SRCS 	=main.c\
		reference.c\
		inputs.c\
		choose.c\
		utils.c\
		error.c\
		des.c
HASH	=hash.c\
		md5.c\
		sha224.c\
		sha256.c\
		sha384.c\
		sha512.c
RSA		=ssl_rsa.c\
		genrsa.c \
		is_primary.c \
		rsa.c \
		rsa_out.c

RU_DEB	=_DEBUG_RULE_
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(HASH:.c=.o))



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

$(NAME): $(ARCHIVE) $(OBJ)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[:##        :]\r"
		@gcc $(CFLAGS) -Werror $(OBJ_PATH)/*.o $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[:##########:]\n"

q:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc $(CFLAGS) -g $(addprefix srcs/,$(SRCS)) $(addprefix srcs/hash/,$(HASH)) $(addprefix srcs/rsa/,$(RSA)) $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG)OK!$(NC)]\n" #PRINT

debug:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc -D$(RU_DEB) $(CFLAGS) -g $(addprefix srcs/,$(SRCS)) $(addprefix srcs/hash/,$(HASH)) $(addprefix srcs/rsa/,$(RSA)) $(ARCHIVE) -o $(NAME)
		@printf "[$(YELLOW)debug$(NC)]\t\t[:##########:]\n"

sanitize:
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):#         :$(NC)]\r"
		@rm -rf $(NAME)
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):##        :$(NC)]\r"
		@rm -rf $(NAME).dSYM
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):###       :$(NC)]\r"
		@gcc -g -Wall -Wextra $(addprefix srcs/,$(SRCS)) $(addprefix srcs/hash/,$(HASH)) $(addprefix srcs/rsa/,$(RSA)) $(ARCHIVE) -o $(NAME) -fsanitize=address
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):##########:$(NC)]\n"

$(OBJ_PATH):
		@mkdir -p $@

$(OBJ_PATH)/%.o: srcs/%.c ft_ssl.h | $(OBJ_PATH)
		@printf "[$(NAME)]\t[:##        :]\r"
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<
$(OBJ_PATH)/%.o: srcs/hash/%.c ft_ssl.h | $(OBJ_PATH)
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<
$(ARCHIVE):
		@make -C libft
