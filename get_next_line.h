/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:55:30 by fsugimot          #+#    #+#             */
/*   Updated: 2020/07/14 22:58:11 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

int		ft_strlen(const char *dst);
void	ft_memcpy(void *dst, void *src, size_t size);
void	*reallocate(char *prev, int add_size, int opt);
int	    get_end_of_line(char *line);
int	    get_next_line(int fd, char **line);

#endif