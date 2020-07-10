/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:46:16 by fsugimot          #+#    #+#             */
/*   Updated: 2020/07/10 16:47:49 by fsugimot         ###   ########.fr       */
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

void	*extend_malloc(char *prev, size_t add_size)
{
	unsigned char	*ret;
	int				mem_size;

	mem_size = ft_strlen(prev) + add_size;
	ret = malloc(mem_size);
	if (!ret)
		return (0);
	while (--mem_size)
		ret[mem_size] = 0;
	if (prev)
	{
		ft_memcpy(ret, prev, ft_strlen(prev));
		free(prev);
	}
	return (void *) ret;
}

int	get_end_of_line(char *line)
{
	size_t	size;

	size = 0;
	while (*line && *line != '\n')
	{
		size++;
		line++;
	}
	return (size);
}

int	get_next_line(int fd, char **line)
{
	static char		*buffer;
	int				read_ret;
	int				cnt;
	int				inc_cnt;

	// check buffer's address
	if (!buffer)
	{
		buffer = extend_malloc(0, BUFFER_SIZE);
		read_ret = read(fd, buffer, BUFFER_SIZE);
	}
	cnt = ft_strlen(buffer);
	inc_cnt = 0;
	// while not line end concat buffer
	while (BUFFER_SIZE == cnt - inc_cnt)
	{
		buffer = extend_malloc(buffer, BUFFER_SIZE);
		if (!buffer)
			return (-1);
		read_ret = read(fd, buffer + cnt, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(buffer);
			return (-1);
		}
		inc_cnt = cnt;
		cnt += read_ret;
	}
	// cut the line from buffer
	inc_cnt = get_end_of_line(buffer);
	ft_memcpy((*line), buffer, inc_cnt + 1);
	if (inc_cnt != cnt)
	{
		ft_memcpy(buffer, (buffer + inc_cnt + 1), cnt - inc_cnt);
		buffer[inc_cnt] = 0;
	}
	line[0][inc_cnt] = '\0';
	if (read_ret == 1)
		free(buffer);
	// return whatever number there is
	return (read_ret != 1 ? 1 : 0);
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
	for (int i = 0; i < 30; i++){
		get_next_line(fd, &c);
		printf("%s\n", c);
	}
	free(c);
}
