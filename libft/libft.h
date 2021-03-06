/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:41:11 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/17 11:32:33 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 16
# define FILEFIN 0
# define ENDL 1
# define ERROR -1
# define CONTINUE 2
# define ABS(C) (C < 0 ? -C : C)

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;
t_list			*ft_lstnew(void const *content, size_t content_size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_swap(void *a, void *b, size_t size);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *bob);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstrev(t_list **lst);
void			ft_memdel(void **ap);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_b(int n, char *base);
void			ft_putnbr_b_fd(int n, char *base, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			die(const char *message);
void			ft_strclr(char *s);
void			ft_strdel(char **ap);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));

void			*ft_memmove(void *str1, const void *str2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *str, int c, size_t n);
void			*ft_memrcpy(void *str1, const void *str2, size_t n);
void			*ft_bzero(void *str, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *str1, const void *str2, int c, size_t n);
void			*ft_memscpy(void *str1, const void *str2, size_t n);
void			*ft_memcpy(void *str1, const void *str2, size_t n);

int				get_next_line(const int fd, char **line);
int				ft_atoi(const char *str);
int				ft_max_i(int lo, int n);
int				ft_min_i(int hi, int n);
int				ft_clamp_i(int hi, int lo, int n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_iswhitespace(int c);
int				ft_atoi_b(const char *str, const char *base);
int				ft_memcmp(const void *str1, const void *str2, size_t n);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_strcmp(const char *str1, const char *str2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_strnrequ(const char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
int				ft_strequ(char const *s1, char const *s2);

double			ft_atod(const char *str);
double			ft_max(double lo, double n);
double			ft_min(double hi, double n);
double			ft_clamp(double hi, double lo, double n);

char			*ft_itoa_b(int n, char *base);
char			*ft_itoa(int n);
char			*ft_ltoa(long n);
char			*ft_dtoa(double n, int precision);
char			*ft_itoa_b(int n, char *base);
char			*ft_strcat(char *ret, const char *str);
char			*ft_strchr(char *str, char c);
char			*ft_strcpy(char *ret, const char *str);
char			*ft_strdup(const char *str);
char			*ft_strmap(char *s, char (*f)(char));
char			*ft_strmapi(char *s, char (*f)(unsigned int, char));
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strjoin_n_free(char *s1, char *s2);
char			*ft_strncat(char *ret, const char *str, size_t n);
char			*ft_strncpy(char *ret, const char *str, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
char			*ft_streplace(char *line, char a, char b);
char			*ft_strrchr(char *str, char c);
char			**ft_strsplit(const char *s, char c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strsub_free(char *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s);

size_t			ft_strlcat(char *dest, const char *src, size_t n);
size_t			ft_strlen(const char *str);

#endif
