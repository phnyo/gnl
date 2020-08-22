/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 21:21:18 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/22 17:37:27 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		fetch_line(int fd, char **line, int ini_i)
{
	int		index;
	int		ret_num;
	char	*tmp;

	index = ini_i;
	if (!line[0])
	{
		if (!(tmp = malloc(sizeof(char))))
			return (-1);
		tmp[0] = 0;
	}
	else
		tmp = line[0];
	while (!tmp[0] || (tmp[0] == '\n' && !tmp[1]) || !is_parsable(tmp, index))
	{
		tmp = add_memback(tmp, BUFFER_SIZE);
		ret_num = read(fd, tmp + index, BUFFER_SIZE);
		if (ret_num <= 0)
			break ;
		index += ret_num;
	}
	tmp[index] = 0;
	line[0] = tmp;
	return (ret_num == -1 ? ret_num : index - ini_i);
}

int		cut_line(char **src, char **dst, int reari)
{
	int	fronti;
	int	ret;

	fronti = 0;
	while (src[0][fronti] && src[0][fronti] != '\n')
		fronti++;
	ret = (src[0][fronti] ? 0 : 1);
	cut_front(src[0], dst, fronti);
	src[0] = cut_back(src[0], fronti, reari);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	**store;
	int			ret;

	if (fd < 0 || !line || !(line[0] = malloc(sizeof(char))))
		return (-1);
	if (!store)
	{
		if (!(store = malloc(sizeof(char *))))
			return (-1);
		store[0] = 0;
	}
	ret = fetch_line(fd, store, (store[0] ? ft_strlen(store[0]) : 0));
	if (!store || ret == -1)
		return (-1);
	ret = cut_line(store, line, ft_strlen(store[0]));
	if (!store)
		return (-1);
	if (ret)
	{
		free(store[0]);
		free(store);
		store = 0;
	}
	return (!ret);
}
