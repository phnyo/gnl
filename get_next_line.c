/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:46:16 by fsugimot          #+#    #+#             */
/*   Updated: 2020/07/14 23:02:41 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*reallocate(char *prev, int add_size, int opt)
{
	unsigned char	*ret;
	int				mem_size;
	int				prev_size;

	prev_size = ft_strlen(prev);
	mem_size = (prev_size > add_size ? add_size * opt + prev_size 
		: add_size + prev_size * opt ) + 1;
	ret = malloc(mem_size);
	if (!ret)
		return (0);
	ret[0] = ret[mem_size - 1] = 0;
	if (prev && *prev)
	{
		if (opt == 1)
			ft_memcpy(ret, prev, mem_size - add_size - 1);
		else
			ft_memcpy(ret, prev + add_size, mem_size - 1);
		free(prev);
	}
	return (void *) ret;
}

int	get_end_of_line(char *line)
{
	size_t	size;

	size = 0;
	while (line && *line && *line != 10)
	{
		size++;
		line++;
	}
	return (size + 1);
}

int	get_next_line(int fd, char **line)
{
	static char *storage;
	int			itr;
	int			read_val;

	itr = get_end_of_line(storage);
	while (1)
	{
		if (!read_val || (storage && storage[itr - 1] == '\n'))
			break;
		if (!(storage = reallocate(storage, BUFFER_SIZE, 1)))
			return (-1);
		if ((read_val = read(fd, storage + itr - 1, BUFFER_SIZE)) == -1)
		{
			free(storage);
			return (-1);
		}
		itr += get_end_of_line(storage + itr - 1) - 1;
	}
	ft_memcpy((*line), storage, itr);
	line[0][itr] = 0;
	if (read_val && storage[itr])
	{
		if (!(storage = reallocate(storage, itr, -1)))
			return (-1);
	} 	
	else
	{
		free(storage);
		storage = 0;
	}
	return (read_val > 0);
}