/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:51:21 by oouhlale          #+#    #+#             */
/*   Updated: 2025/05/31 12:04:23 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include "../includes/minishell.h"
# include <stdlib.h>
# include <unistd.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		only_spaces(const char *str);
int     ft_isalnum(int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strdup2(const char *s1);
char	*ft_strndup(const char *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		is_quote(char c);
int		is_operator(char c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*strjoin_free(char *s1, const char *s2);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memdel(void *ptr);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strcpy(char *dest, const char *src);
void	ft_putendl(char *s);
int	    ft_atoi(const char *str);
int	    ft_strisnum(const char *str);
void	ft_skip_spacenl(const char *str, int *i);
void	free_split(char **split);
int	    ft_isalpha(int c);
int	    ft_isdigit(int c);
void	ft_putstr(char *s);
int     ft_isspace(char c);
long long	ft_atol(const char *str);

#endif
