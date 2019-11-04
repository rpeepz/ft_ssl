# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/13 21:22:38 by rpapagna          #+#    #+#              #
#    Updated: 2019/09/25 17:27:28 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CFLAGS	= -Wall -Werror -Wextra -g
INCL	= -I includes/

#COLOR OUTPUT OPIONS
RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
CYN		=\033[0;36m
NC		=\033[0m

#PATHS
OBJ_PATH	= obj
LIB_PATH	= srcs
PRNTF_PATH	=$(LIB_PATH)/ft_printf
SPRNTF_PATH	=$(LIB_PATH)/ft_sprintf

SRCS	= ft_abs.c \
		ft_atoi.c \
		ft_itoa_base.c \
		ft_islower.c \
		ft_isupper.c \
		ft_isvariants.c \
		ft_lstadd.c \
		ft_lstnew.c \
		ft_map.c \
		ft_memalloc.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_pipewrench.c \
		ft_printf.c \
		ft_putchar.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_sprintf.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strnew.c \
		ft_strpop.c \
		ft_strsplit.c \
		ft_strstr.c \
		get_next_line.c
PRINTF	= finders.c \
		do_things.c \
		get_mods.c \
		convert_b.c \
		convert_c.c \
		convert_f.c \
		convert_i.c \
		convert_o.c \
		convert_p.c \
		convert_s.c \
		convert_u.c \
		convert_x.c \
		convert_percent.c
SPRINTF	= get_mod.c \
		c_to_buf.c \
		i_to_buf.c \
		s_to_buf.c \
		u_to_buf.c \
		x_to_buf.c

OBJ = $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_PATH)/,$(PRINTF:.c=.o))
OBJ += $(addprefix $(OBJ_PATH)/,$(SPRINTF:.c=.o))

.PHONY: clean

all: $(NAME)

clean:
		@printf "[rm      obj]\t[:          :]\r"
		@rm -f $(OBJ)
		@printf "[$(RED)clean libft$(NC)]\t[:##########:]\r"

fclean: clean
		@printf "[rm    libft]\t[:          :]\r"
		@rm -rf $(OBJ_PATH)
		@rm -rf $(NAME)
		@printf "[$(RED)full  clean$(NC)]\t[:##########:]\r"

re: fclean all

$(NAME): $(OBJ)
		@printf "[make  libft]\t[:######### :]\r"
		@ar -rcs $(NAME) $(OBJ)
		@printf "[$(CYN)make  libft$(NC)]\t[:##########:]\n"

$(OBJ_PATH):
		@printf "[make  libft]\t[:#         :]\r"
		@mkdir -p $@

$(OBJ_PATH)/%.o: $(LIB_PATH)/%.c | $(OBJ_PATH)
		@printf "[make  libft]\t[:###       :]\r"
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<

$(OBJ_PATH)/%.o: $(PRNTF_PATH)/%.c | $(OBJ_PATH)
		@printf "[make  libft]\t[:#####     :]\r"
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<

$(OBJ_PATH)/%.o: $(SPRNTF_PATH)/%.c | $(OBJ_PATH)
		@printf "[make  libft]\t[:#######   :]\r"
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<
