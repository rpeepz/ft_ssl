# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/01 20:19:37 by rpapagna          #+#    #+#              #
#    Updated: 2019/11/16 17:51:58 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ssl
ARCHIVE = libft/libft.a
AUTHOR	= rpapagna

CFLAGS	= -Wall -Wextra
INCL	= includes/
OBJ_PATH= obj

#COLOR OUTPUT OPIONS
RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
MAG		=\033[0;35m
NC		=\033[0m

SRCS 	=main.c\
		inputs.c\
		choose.c\
		error.c
HASH	=hash.c\
		md5.c\
		sha224.c\
		sha256.c\
		sha384.c\
		sha512.c
ENCODE	=encode.c \
		base64_print.c
RSA		=ssl_rsa.c\
		genrsa.c \
		is_primary.c \
		rsa.c \
		rsa_out.c \
		asn1.c
UTIL	=maths.c \
		reference.c \
		in.c

RU_DEB	=_DEBUG_RULE_
OBJ		= $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(HASH:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(ENCODE:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(RSA:.c=.o))
OBJ		+= $(addprefix $(OBJ_PATH)/,$(UTIL:.c=.o))

QSRCS	= $(addprefix srcs/,$(SRCS))
QSRCS	+= $(addprefix srcs/hash/,$(HASH))
QSRCS	+= $(addprefix srcs/encode/,$(ENCODE))
QSRCS	+= $(addprefix srcs/rsa/,$(RSA))
QSRCS	+= $(addprefix srcs/util/,$(UTIL))

.PHONY: clean debug

all:	$(NAME)

clean:
		@printf "[$(RED)clean   obj$(NC)]\t[:#         :]\r"
		@make -C libft clean
		@printf "[$(RED)clean   obj$(NC)]\t[:#######   :]\r"
		@rm -f $(OBJ)
		@printf "[$(RED)clean   obj$(NC)]\t[:##########:]\n"

fclean: clean
		@make -C libft fclean
		@printf "[$(RED)full  clean$(NC)]\t[:######    :]\r"
		@rm -rf $(OBJ_PATH)
		@rm -rf $(NAME).dSYM
		@rm -rf $(NAME).h.gch
		@rm -rf $(NAME)
		@printf "[$(RED)full  clean$(NC)]\t[:##########:]\n"

re: fclean all

$(NAME): $(ARCHIVE) $(OBJ)
		@printf "[$(NAME)]\t[:#######   :]\r"
		@gcc $(CFLAGS) -Werror $(OBJ_PATH)/*.o $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[:##########:]\n"

q:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc $(CFLAGS) -g -I $(INCL) $(QSRCS) $(ARCHIVE) -o $(NAME)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG)OK!$(NC)]\n" #PRINT

debug:
		@rm -rf $(NAME)
		@rm -rf $(NAME).dSYM
		@gcc -D$(RU_DEB) $(CFLAGS) -g -I $(INCL) $(QSRCS) $(ARCHIVE) -o $(NAME)
		@printf "[$(YELLOW)debug$(NC)]\t\t[:##########:]\n"

sanitize:
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):#         :$(NC)]\r"
		@rm -rf $(NAME)
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):##        :$(NC)]\r"
		@rm -rf $(NAME).dSYM
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):###       :$(NC)]\r"
		@gcc -g $(CFLAGS) -I $(INCL) $(QSRCS) $(ARCHIVE) -o $(NAME) -fsanitize=address
		@printf "[$(YELLOW)sanitize$(NC)]\t[$(RED):##########:$(NC)]\n"

$(OBJ_PATH):
		@printf "[$(GREEN)$(NAME)$(NC)]\t[:#         :]\r"
		@mkdir -p $@

$(OBJ_PATH)/%.o: srcs/%.c includes/ft_ssl.h | $(OBJ_PATH)
		@printf "[$(NAME)]\t[:##        :]\r"
		@gcc $(CFLAGS) -I $(INCL) -o $@ -c $<
$(OBJ_PATH)/%.o: srcs/hash/%.c includes/hash.h | $(OBJ_PATH)
		@printf "[$(NAME)]\t[:###       :]\r"
		@gcc $(CFLAGS) -I $(INCL) -o $@ -c $<
$(OBJ_PATH)/%.o: srcs/encode/%.c includes/encode.h | $(OBJ_PATH)
		@printf "[$(NAME)]\t[:####      :]\r"
		@gcc $(CFLAGS) -I $(INCL) -o $@ -c $<
$(OBJ_PATH)/%.o: srcs/rsa/%.c includes/rsa.h | $(OBJ_PATH)
		@printf "[$(NAME)]\t[:######    :]\r"
		@gcc $(CFLAGS) -I $(INCL) -o $@ -c $<
$(OBJ_PATH)/%.o: srcs/util/%.c includes/ft_ssl.h | $(OBJ_PATH)
		@printf "[$(NAME)]\t[:#######   :]\r"
		@gcc $(CFLAGS) -I $(INCL) -o $@ -c $<
$(ARCHIVE):
		@make -C libft
