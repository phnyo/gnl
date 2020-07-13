/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:46:16 by fsugimot          #+#    #+#             */
/*   Updated: 2020/07/13 13:26:50 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *dst)
{
	int	ret;

	ret = 0;
	if (dst)
		while (*dst++)
			ret++;
	return (ret);
}

void	ft_memcpy(void *dst, void *src, size_t size)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	dst_p = dst;
	src_p = src;
	while (size--)
	{
		*dst_p = *src_p;
		dst_p++;
		src_p++;
	}
}

void	*reallocate(char *prev, int add_size, int opt)
{
	unsigned char	*ret;
	int				mem_size;

	mem_size = ft_strlen(prev) + add_size * opt + 1;
	ret = malloc(mem_size);
	if (!ret)
		return (0);
	ret[mem_size - 1] = 0;
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
		if (storage && storage[itr - 1] == '\n')
			break;
		if (!(storage = reallocate(storage, BUFFER_SIZE, 1)))
			return (-1);
		if ((read_val = read(fd, storage + itr - 1, BUFFER_SIZE)) == -1)
		{
			free(storage);
			line[0][0] = 0;
			return (-1);
		}
		if (!read_val)
			break ;
		itr += get_end_of_line(storage + itr);
	}
	ft_memcpy((*line), storage, itr);
	line[0][itr] = 0;
	if (storage[itr])
		storage = reallocate(storage, itr, -1);
	else
	{
		free(storage);
		storage = 0;
	}
	return (read_val > 0);
}

#include<limits.h>

int main(int argc, char **argv)
{
	int fd;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = -1;
	char *c = malloc(sizeof(char) * INT_MAX);
	while (get_next_line(fd, &c) == 1)
		printf("%s", c);
	free(c);
}
