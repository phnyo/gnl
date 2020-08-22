/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:57:14 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/22 17:32:51 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *line)
{
	int	index;

	index = 0;
	while (line[index])
		index++;
	return (index);
}

int		is_parsable(char *line, int ind)
{
	int	index;

	index = ind - BUFFER_SIZE;
	if (index < 0)
		index = 0;
	while (line[index] && line[index] != '\n' && index < ind)
		index++;
	return (index != ind);
}

char	*add_memback(char *line, int size)
{
	char	*ret;
	int		alloc_size;
	int		index;

	index = 0;
	alloc_size = ft_strlen(line) + size;
	ret = malloc(alloc_size + 1);
	if (ret)
	{
		ret[alloc_size] = 0;
		while (index < alloc_size - size)
		{
			ret[index] = line[index];
			++index;
		}
	}
	free(line);
	return (ret);
}

char	*cut_back(char *line, int front, int back)
{
	char	*ret;
	int		itr;

	itr = back - front;
	ret = malloc(itr + 1);
	if (ret)
	{
		while (itr)
		{
			ret[itr - 1] = line[itr + front];
			itr--;
		}
	}
	free(line);
	return (ret);
}

void	cut_front(char *src, char **dst, int back)
{
	char	*ret;
	int		itr;

	itr = back;
	ret = malloc(itr + 1);
	if (ret)
	{
		ret[itr--] = 0;
		while (itr > -1)
		{
			ret[itr] = src[itr];
			itr--;
		}
	}
	free(dst[0]);
	dst[0] = ret;
}
