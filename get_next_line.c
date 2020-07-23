/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:46:16 by fsugimot          #+#    #+#             */
/*   Updated: 2020/07/21 08:26:39 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		all_free(char **store)
{
	int	itr;

	if (store)
	{
		itr = 0;
		while (store[itr])
		{
			free(store[itr]);
			itr++;
		}
		free(store);
	}
	return (-1);
}

void	null_clear(char **src)
{
	int itr;

	itr = 0;
	while (itr < 256)
		src[itr++] = 0;
}

int		check_threads(char **src)
{
	int	itr;

	itr = 256;
	while (itr)
	{
		if (src[itr])
			return (1);
		--itr;
	}
	return (0);
}

int		ft_strlen(const char *src)
{
	int	ret;

	ret = 0;
	while (*src)
	{
		++ret;
		++src;
	}
	return (ret);
}

void	ft_memcpy(void *dst, void *src, size_t mem_size)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	dst_ptr = dst;
	src_ptr	= src;
	while (mem_size)
	{
		*dst_ptr = *src_ptr;
		++dst_ptr;
		++src_ptr;
		--mem_size;
	}
}

char	*concat(char *src, int size, int flg)
{
	char	*ret;
	int		mem_size;

	if (!src)
		mem_size = size + 1;
	else
		mem_size = ft_strlen(src) + size * flg + 1;
	ret = malloc(mem_size);
	if (!ret)
		return (0);
	ret[0] = 0;
	ret[mem_size - 1] = 0;
	if (flg == 1)
		ft_memcpy(ret, src, mem_size - size - 1);
	else
		ft_memcpy(ret, src + size, mem_size - 1);
	free(src);
	return (ret);
}

int		find_new_line(char *src)
{
	int	itr;

	itr = 0;
	while (src[itr] && src[itr] != '\n')
		++itr;
	if (src[itr] == '\n')
		++itr;
	return (itr);
}

int		capture_line(char **dst, int fd)
{
	int	ret;
	int	tmp;

	ret = dst[0] ? ft_strlen(dst[0]) : 0;
	while (1)
	{
		dst[0] = concat(dst[0], BUFFER_SIZE, 1);	
		if (!dst[0])
			return (-1);
		if ((tmp = read(fd, dst[0] + ret, BUFFER_SIZE)) <= 0)
			ret = tmp;
		else
			ret += find_new_line(dst[0] + ret);
		if (ret <= 0 || !dst[0][ret - 1] || dst[0][ret - 1] == '\n')
			break;
	}
	dst[1] = concat(dst[1], ft_strlen(dst[0]) - ret, 1);
	ft_memcpy(dst[1], dst[0] + ret, ft_strlen(dst[0]) - ret);
	dst[0] = concat(dst[0], ret, 1);
	dst[0][ret - 1] = 0;
	return (ret);
}

char	*process_line(char *dst, char *src)
{
	int		src_size;

	free(dst);
	src_size = ft_strlen(src);
	if (!(dst = malloc(src_size + 1)))
		return (0);
	ft_memcpy(dst, src, src_size);
	dst[src_size] = 0;
	return (dst);
}

int	get_next_line(int fd, char **line)
{
	static char	**store;
	int			ret_val;

	fd = fd > 0 ? fd : -1;
	if (fd > 0 && !store)
		null_clear(store = malloc(sizeof(char *) * 258));
	if (fd > 0)
		ret_val = capture_line(&store[fd - 1], fd);
	if (fd < 0 || ret_val == -1)
		return (all_free(store));
	if (!(line[0] = process_line(line[0], store[fd - 1])))
	{
		free(store[fd - 1]);
		return (-1);
	}
	if(store[fd][0] && !(store[fd - 1] = concat(store[fd], ret_val - ft_strlen(store[fd]), -1)))
		return (-1);
	if (!ret_val || !store[fd - 1][ret_val])
	{
		free(store[fd - 1]);
		store[fd - 1] = 0;
	}
	if (!check_threads(store))
		free(store);
	return (ret_val > 0);
}
