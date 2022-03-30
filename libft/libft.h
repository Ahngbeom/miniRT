/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:23:34 by jseol             #+#    #+#             */
/*   Updated: 2022/03/30 18:34:38 by jaeyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strncpy(char *dest, char *src, int n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *h, const char *n, size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_atoi_base(char *str, char *base);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_isspace(const char c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strstr(char *str, char *to_find);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *l, void *(*f)(void*), void (*d)(void*));

size_t				ft_gnl_strlen(char *s);
size_t				ft_gnl_strlcpy(char *dest, const char *src, size_t dstsize);
size_t				ft_gnl_strlcat(char *dest, const char *src, size_t dstsize);
char				*ft_gnl_strdup(char *s);
char				*ft_gnl_strjoin(char *s1, char *s2);
int					ft_strchr_index(char *s, char c);
int					ft_newline_line(char **store, size_t index, char **line);
int					ft_eof_line(char **store, char **line, int read_size);
int					get_next_line(int fd, char **line);

char				*ft_strupcase(char *str);
double				ft_atod(char *str);

#endif
