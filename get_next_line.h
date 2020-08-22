/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:55:30 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/22 17:42:13 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int		ft_strlen(const char *dst);
int		is_parsable(char *line, int ind);
char	*add_memback(char *line, int size);
int		fetch_line(int fd, char **line, int ini_i);
char	*cut_back(char *line, int front, int back);
void	cut_front(char *src, char **dst, int back);
int		cut_line(char **src, char **dst, int reari);
int     get_next_line(int fd, char **line);

#endif
