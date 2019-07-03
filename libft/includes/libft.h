/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:14:12 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 04:24:58 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>

/*
**	----- ----- -----
**	MACROS
**	----- ----- -----
*/

# define MAX_FD 4096
# define PAGESIZE 4096
# define GNL_BUFF_SIZE 2

# define ADD_ONE_TO_BUFF(buf, c, n) ft_strncpy(buf, c, 1); buf++; n++;
# define ADD_TO_BUFF(buf, src, n, ln) ft_strncpy(buf, src, ln); buf+=ln; n+=ln;
# define LEN(X) (int)ft_strlen(X)
# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\r' || x == '\f')
# define IF_THEN(X, Y) if(X) {(Y);}
# define IF_RETURN(X, Y) if(X) {return (Y);}
# define PIPE_KEY '-'

/*
**	----- ----- -----
**	STRUCTS
**	----- ----- -----
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_flag
{
	int				space;
	int				pound;
	int				minus;
	int				fplus;
	int				fzero;
}					t_flag;

typedef struct		s_mods
{
	t_flag			fl;
	int				width;
	int				prcsn;
	int				length;
}					t_mods;

typedef struct		s_fl
{
	int				space;
	int				pound;
	int				minus;
	int				fplus;
	int				fzero;
}					t_fl;

typedef struct		s_mod
{
	t_fl			fl;
	int				width;
	int				prcsn;
	int				length;
	int				neg;
}					t_mod;

/*
**	----- ----- -----
**	STR
**	----- ----- -----
*/

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strchri(const char *s, int c);
char				*ft_strstr(const char *s, const char *to_find);
char				*ft_strnstr(const char *s, const char *to_find, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

char				*ft_strnew(size_t size);
char				*ft_strcnew(size_t len, char c);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*str_3join(char const *s1, char const *s2, char const *s3);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
**	----- ----- -----
**	IS
**	----- ----- -----
*/

int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					is_flag(char x);

/*
**	----- ----- -----
**	MEM
**	----- ----- -----
*/

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *dst, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

/*
**	----- ----- -----
**	PUT
**	----- ----- -----
*/

void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnstr(const char *s, int len);

/*
**	----- ----- -----
**	PROJECT
**	----- ----- -----
*/

int					get_next_line(const int fd, char **line);
int					ft_pipewrench(char *str, ...);
int					ft_printf(char *str, ...);
int					ft_sprintf(char *buf, char *str, ...);

/*
**	----- ----- -----
**	STRUCT OPS
**	----- ----- -----
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
**	----- ----- -----
**	UTILS
**	----- ----- -----
*/
int					ft_countwords(char const *s, char c);
int					ft_intlen(int num);
int					ft_atoi(const char *s);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base);
char				*ft_uitoa_base(unsigned int n, int base);
char				*ft_strpop(char *str, size_t id);

void				set_flags(t_flag *fl, char c);

char				*num_string_base(long long num, int base);
char				*num_string_u_base(unsigned long long num, int base);
void				print_one(char **str);
int					ft_padding(char *buf, int len, t_mod mod, int nbyte);
void				left_jut(char *buf, char *num, t_mod mod, int nbyte);

t_mods				get_mods(char **str, va_list ap);
t_mod				get_mod(char **str, va_list ap);

int					get_type_specifier(char x);
int					get_pre_float(long double number, int ret);
int					get_undef_length(char x);

int					convert_percent(t_mods modifiers);
int					convert_i(t_mods modifiers, va_list ap);
int					convert_c(t_mods modifiers, va_list ap);
int					convert_s(t_mods modifiers, va_list ap);
int					convert_p(t_mods modifiers, va_list ap);
int					convert_o(t_mods modifiers, va_list ap, int i);
int					convert_u(t_mods modifiers, va_list ap, int i);
int					convert_x(t_mods modifiers, va_list ap, int i);
int					convert_f(t_mods modifiers, va_list ap, int i);
int					convert_b(t_mods modifiers, va_list ap, int i);

int					c_to_buf(char *buf, t_mod modifiers, va_list ap);
int					i_to_buf(char *buf, t_mod modifiers, va_list ap);
int					s_to_buf(char *buf, t_mod modifiers, va_list ap);
int					x_to_buf(char *buf, t_mod modifiers, va_list ap, int i);

#endif
