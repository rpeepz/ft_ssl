# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/13 21:22:38 by rpapagna          #+#    #+#              #
#    Updated: 2019/06/20 04:56:49 by rpapagna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CFLAGS	= -Wall -Werror -Wextra -g
INCL	= -I includes/

#COLOR OUTPUT OPIONS
RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[0;33m
MAG		=\033[0;35m
NC		=\033[0m

#PATHS
OBJ_PATH	= obj
LIB_PATH	= srcs
PRNTF_PATH	=$(LIB_PATH)/ft_printf
SPRNTF_PATH	=$(LIB_PATH)/ft_sprintf

SRCS	= ft_atoi.c \
		ft_bzero.c \
		ft_countwords.c \
		ft_intlen.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_islower.c \
		ft_isprint.c \
		ft_isupper.c \
		ft_itoa_base.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_pipewrench.c \
		ft_printf.c \
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putendl_fd.c \
		ft_putendl.c \
		ft_putnbr_fd.c \
		ft_putnbr.c \
		ft_putstr_fd.c \
		ft_putstr.c \
		ft_sprintf.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strchri.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcnew.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strpop.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
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
		x_to_buf.c

OBJ = $(addprefix $(OBJ_PATH)/,$(SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_PATH)/,$(PRINTF:.c=.o))
OBJ += $(addprefix $(OBJ_PATH)/,$(SPRINTF:.c=.o))

FILES = $(addprefix $(LIB_PATH)/,$(SRCS))
FILES += $(addprefix $(PRNTF_PATH)/,$(PRINTF))
FILES += $(addprefix $(SPRNTF_PATH)/,$(SPRINTF))

.PHONY: clean

all: $(NAME)

clean:
		@printf "[$(RED)obj$(NC)]\t\tRm objects\n" #PRINT
		@rm -rf obj

fclean: clean
		@printf "[$(RED)$(NAME)$(NC)]\tRm archive\n"
		@rm -rf $(NAME)

re: fclean all

$(NAME): $(OBJ)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG):\:$(NC)]\r" #PRINT
		@ar -rcs $(NAME) $(OBJ)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG)OK!$(NC)]\n" #PRINT

$(OBJ_PATH):
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG):\:$(NC)]\r" #PRINT
		@mkdir -p $@

$(OBJ_PATH)/%.o: $(LIB_PATH)/%.c | $(OBJ_PATH)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG):/:$(NC)]\r" #PRINT
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<

$(OBJ_PATH)/%.o: $(PRNTF_PATH)/%.c | $(OBJ_PATH)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG):\:$(NC)]\r" #PRINT
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<

$(OBJ_PATH)/%.o: $(SPRNTF_PATH)/%.c | $(OBJ_PATH)
		@printf "[$(GREEN)$(NAME)$(NC)]\t[$(MAG):/:$(NC)]\r" #PRINT
		@gcc $(CFLAGS) $(INCL) -o $@ -c $<
