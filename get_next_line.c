/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:46:16 by fsugimot          #+#    #+#             */
/*   Updated: 2020/07/13 14:25:42 by fsugimot         ###   ########.fr       */
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

int	get_end_of_line(char *line)
{
	size_t	size;

	size = 0;
	while (line && *line && *line != '\n')
	{
		size++;
		line++;
	}
	return (size + 1);
}

void	*reallocate(char *prev, int add_size, int opt)
{
	unsigned char	*ret;
	int				mem_size;

	mem_size = ft_strlen(prev) + 1 + add_size * opt;
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

int	get_next_line(int fd, char **line)
{
	static char *storage;
	int			itr;
	int			read_val;

	itr = get_end_of_line(storage);
	line[0] = reallocate(line[0], itr, 1);
	if (!line[0])
		return (-1);
	if (storage)
		ft_memcpy(line[0], storage, itr);
	while (1)
	{
		if ()
		{
			ft_memcpy 
			line[0][itr] = 0;
			return (1);
		}
		line[0] = reallocate(line[0], BUFFER_SIZE, 1);
		if (!line[0])
			return (-1);
		read_val = read(fd, line[0], BUFFER_SIZE);
		if (read_val == -1)
		{
			free(line[0]);
			return (-1);
		}
		if (!read_val)
			return (0);
		itr += get_end_of_line(line[0][itr]);
	}
	return (1);
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
	printf("%s", c);
	free(c);
}
